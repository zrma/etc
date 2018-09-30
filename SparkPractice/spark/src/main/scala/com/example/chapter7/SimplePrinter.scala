package com.example.chapter7

import akka.actor.{Actor, Props}
import org.apache.spark.internal.Logging
import org.apache.spark.streaming.{Milliseconds, StreamingContext}
import org.apache.spark.streaming.akka.ActorReceiver

case class SimplePrinterConfig(hostname: String = "localhost",
                               port: Int = 12345,
                               interval: Int = 1000)

class SimpleReceiver(urlOfPublisher: String) extends ActorReceiver {

  lazy private val remotePublisher = context.actorSelection(urlOfPublisher)

  override def preStart(): Unit =
    remotePublisher ! SubscribeReceiver(context.self)

  def receive: PartialFunction[Any, Unit] = {
    case msg => store(msg)
  }

  override def postStop(): Unit =
    remotePublisher ! UnsubscribeReceiver(context.self)

}

object SimplePrinter extends Logging {
  def main(args: Array[String]) {

    val parser = new scopt.OptionParser[SimplePrinterConfig]("SimplePrinter") {
      arg[String]("hostname") required () action { (x, c) =>
        c.copy(hostname = x)
      } text "The hostname to accept connections from remote hosts"

      arg[Int]("port") required () action { (x, c) => c.copy(port = x)
      } text "The port number to accept connections from remote hosts"

      arg[Int]("interval") required () action { (x, c) => c.copy(interval = x)
      } text "The interval to process data [msec]"
    }

    parser.parse(args, SimplePrinterConfig()) exists { config =>
      import org.apache.spark.sql.SparkSession
      import org.apache.spark.streaming.akka.AkkaUtils
      val ss = SparkSession
        .builder()
        .master("local[*]")
        .appName("ActorWordCount")
        .getOrCreate()
      val ssc =
        new StreamingContext(ss.sparkContext, Milliseconds(config.interval))

      val lines = AkkaUtils.createStream[String](
        ssc,
        Props(
          classOf[SimpleReceiver],
          "akka.tcp://test@%s:%s/user/Feeder"
            .format(config.hostname, config.port)
        ),
        "SimpleReceiver"
      )

      lines.print()

      ssc.start()
      ssc.awaitTermination()
      ssc.stop()

      true
    }
  }
}
