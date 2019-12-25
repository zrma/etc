package com.example.chapter5

import org.apache.spark.{SparkConf, SparkContext}

object WordCount {
  def main(args: Array[String]): Unit = {
    require(args.length >= 1, "parameter needs - file path")

    val conf = new SparkConf().setAppName("WordCount").setMaster("local[*]")
    val sc = new SparkContext(conf)

    try {
      val filePath = args(0)
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
