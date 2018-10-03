package com.example.chapter7

import org.apache.log4j.{Level, Logger}
import org.apache.spark.internal.Logging
import org.apache.spark.sql.SparkSession
import org.apache.spark.storage.StorageLevel
import org.apache.spark.streaming.{Seconds, StreamingContext}

case class SimpleReceiverConfig(hostname: String = "localhost",
                                port: Int = 12345,
                                interval: Int = 1000)

object SimpleFeedReceiver extends Logging {
  def main(args: Array[String]) {

    val parser = new scopt.OptionParser[SimpleReceiverConfig]("SimplePrinter") {
      arg[String]("hostname") required () action { (x, c) =>
        c.copy(hostname = x)
      } text "The hostname to accept connections from remote hosts"

      arg[Int]("port") required () action { (x, c) => c.copy(port = x)
      } text "The port number to accept connections from remote hosts"

      arg[Int]("interval") required () action { (x, c) => c.copy(interval = x)
      } text "The interval to process data [msec]"
    }

    parser.parse(args, SimpleReceiverConfig()) exists { config =>
      Logger.getRootLogger.setLevel(Level.WARN)

      val ss = SparkSession
        .builder()
        .master("local[*]")
        .appName("SimplePrinter")
        .getOrCreate()
      val ssc = new StreamingContext(ss.sparkContext, Seconds(1))

      val lines = ssc.socketTextStream(
        config.hostname,
        config.port,
        StorageLevel.MEMORY_AND_DISK_SER
      )

      lines.print()
      ssc.start()
      ssc.awaitTermination()

      true
    }
  }
}
