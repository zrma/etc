package com.example.chapter7

import org.apache.spark.sql.SparkSession
import org.apache.spark.streaming.{Seconds, StreamingContext}
import org.apache.log4j.{Level, Logger}
import org.apache.spark.storage.StorageLevel

// NOTE - command $ nc -lk 9999
object SparkStreaming {
  def main(args: Array[String]): Unit = {
    Logger.getRootLogger.setLevel(Level.WARN)

    val ss = SparkSession
      .builder()
      .master("local[*]")
      .appName("SparkStreaming")
      .getOrCreate()
    val ssc = new StreamingContext(ss.sparkContext, Seconds(10))

    val lines =
      ssc.socketTextStream("localhost", 9999, StorageLevel.MEMORY_AND_DISK_SER)
    val words = lines.flatMap(_.split(" ")).filter(_.nonEmpty)
    val pairs = words.map((_, 1))
    val wordCounts = pairs.reduceByKey(_ + _)

    wordCounts.print()
    ssc.start()
    ssc.awaitTermination()
  }
}
