package com.example.chapter5

import org.apache.spark.{SparkConf, SparkContext}

import scala.collection.mutable.ArrayBuffer

object WordCount {
  def main(args: Array[String]): Unit = {
    var params = new ArrayBuffer[String]()
    try {
      require(args.length >= 1, "parameter needs - file path")
    } catch {
      case _: IllegalArgumentException => {
        params += "data/chapter5/README.md"
      }
    }

    val conf = new SparkConf().setAppName("WordCount").setMaster("local[*]")
    val sc = new SparkContext(conf)

    try {
      val Array(filePath) = params.toArray.take(1)
      val wordCntRDD =
        sc.textFile(filePath)
          .flatMap(_.split("[ ,.]"))
          .filter(_.matches("""\p{Alnum}+"""))
          .map((_, 1))
          .reduceByKey(_ + _)
          .sortByKey(ascending = true)
          .map({ case (count, word) => (word, count) })
          .sortByKey(ascending = false)
          .take(3)

      wordCntRDD.foreach(println)
    } finally {
      sc.stop()
    }
  }
}
