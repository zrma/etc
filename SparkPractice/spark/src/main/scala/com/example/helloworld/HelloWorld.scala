package com.example.helloworld

import org.apache.spark.{SparkConf, SparkContext}

object HelloWorld {
  def main(args: Array[String]): Unit = {
    val conf = new SparkConf().setAppName("HellWorld").setMaster("local")
    val sc = new SparkContext(conf)

    val logFile = "README.md"
    val logData = sc.textFile(logFile, 2).cache()

    val lineCount = logData.count()
    println(lineCount)

    sc.stop()
  }
}
