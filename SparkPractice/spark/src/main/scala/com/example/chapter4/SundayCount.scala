package com.example.chapter4

import org.apache.spark.{SparkConf, SparkContext}

import org.joda.time.{DateTime, DateTimeConstants}
import org.joda.time.format.DateTimeFormat

object SundayCount {
  def main(args: Array[String]): Unit = {
    var filePath = "data/chapter4/date.txt": String
    if (args.length > 0) {
      filePath = args(0);
    }

    val conf = new SparkConf().setAppName("SundayCount").setMaster("local")
    val sc = new SparkContext(conf)

    try {
      val textRDD = sc.textFile(filePath)

      val dateTimeRDD = textRDD.map(dateStr => {
        val pattern = DateTimeFormat.forPattern("yyyyMMdd")
        DateTime.parse(dateStr, pattern)
      })

      val sundayRDD = dateTimeRDD.filter(
        dateTime => dateTime.getDayOfWeek == DateTimeConstants.SUNDAY
      )

      val numOfSunday = sundayRDD.count
      println(s"$numOfSunday found")
    } finally {
      sc.stop()
    }
  }
}
