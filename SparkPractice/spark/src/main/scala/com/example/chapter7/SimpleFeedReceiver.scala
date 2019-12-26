package com.example.chapter7

import org.apache.log4j.{Level, Logger}
import org.apache.spark.internal.Logging
import org.apache.spark.sql.SparkSession
import org.apache.spark.storage.StorageLevel
import org.apache.spark.streaming.{Seconds, StreamingContext}

import scala.collection.mutable.ArrayBuffer

case class SimpleReceiverConfig(hostname: String = "localhost",
                                port: Int = 12345,
                                interval: Int = 1000)

object SimpleFeedReceiver extends Logging {
  def main(args: Array[String]) {
    var params = new ArrayBuffer[String]()
    params ++= args
    if (args.length == 0) {
      params += "localhost"
      params += "12345"
      params += "1000"
    }

    Parser.receiver().parse(params.result(), SimpleReceiverConfig()) exists { config =>
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
