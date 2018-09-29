package com.example.chapter5

import org.apache.spark.util.AccumulatorV2
import org.apache.spark.SparkConf
import org.apache.spark.SparkContext
import org.apache.spark.rdd.RDD

case class Accumulator(initialValue: Int = 0, initialDescription: String = "")
    extends AccumulatorV2[Int, Int] {
  private var _value = new Integer(initialValue)
  private val _description = new String(initialDescription)
  override def value: Int = _value
  override def isZero: Boolean = value == 0
  override def copy(): AccumulatorV2[Int, Int] = Accumulator(value, description)
  override def reset(): Unit = _value = new Integer(0)
  override def add(v: Int): Unit = _value = value + v
  override def merge(other: AccumulatorV2[Int, Int]): Unit = add(other.value)
  def description: String = _description
}

object QuestionnaireSummarize {
  private def computeAllAvg(rdd: RDD[(Int, String, Int)]) = {
    val (totalPoint, cnt) = rdd.map(record => (record._3, 1)).reduce {
      case ((lPoint, lCnt), (rPoint, rCnt)) => (lPoint + rPoint, lCnt + rCnt)
    }
    totalPoint / cnt.toDouble
  }

  private def computeAgeRangeAvg(rdd: RDD[(Int, String, Int)]) = {
    rdd
      .map(record => (record._1, (record._3, 1)))
      .reduceByKey {
        case ((lPoint, lCnt), (rPoint, rCnt)) => (lPoint + rPoint, lCnt + rCnt)
      }
      .map {
        case (ageRange, (totalPoint, cnt)) =>
          (ageRange, totalPoint / cnt.toDouble)
      }
      .collect()
  }

  private def computeGenderAvg(rdd: RDD[(Int, String, Int)],
                               numMAcc: Accumulator,
                               totalPointMAcc: Accumulator,
                               numFAcc: Accumulator,
                               totalPointFAcc: Accumulator) = {
    rdd.foreach {
      case (_, maleOrFemale, point) =>
        maleOrFemale match {
          case "M" =>
            numMAcc.add(1)
            totalPointMAcc.add(point)
          case "F" =>
            numFAcc.add(1)
            totalPointFAcc.add(point)
        }
    }

    Seq(
      ("Male", totalPointMAcc.value / numMAcc.value.toDouble),
      ("Female", totalPointFAcc.value / numFAcc.value.toDouble)
    )
  }

  def main(args: Array[String]): Unit = {
    require(args.length >= 1, """
            |args1 : <CSV 파일 경로>
        """.stripMargin)

    val conf = new SparkConf()
      .setAppName("QuestionnaireSummarize")
      .setMaster("local")
      .set("spark.serializer", "org.apache.spark.serializer.KryoSerializer")
    val sc = new SparkContext(conf)

    try {
      val filePath = args(0)

      val questionnaireRDD = sc.textFile(filePath).map { record =>
        val splitRecord = record.split(",")
        val ageRange = (splitRecord(0).toInt / 10) * 10
        val gender = splitRecord(1)
        val point = splitRecord(2).toInt
        (ageRange, gender, point)
      }

      questionnaireRDD.cache()

      val avgAll = computeAllAvg(questionnaireRDD)
      val avgAgeRange = computeAgeRangeAvg(questionnaireRDD)

      val numMAcc = Accumulator(0, "Number of Male")
      val totalPointMAcc = Accumulator(0, "Total Point of Male")
      val numFAcc = Accumulator(0, "Number of Female")
      val totalPointFAcc = Accumulator(0, "Total Point of Female")

      sc.register(numMAcc, "Number of Male")
      sc.register(totalPointMAcc, "Total Point of Male")
      sc.register(numFAcc, "Number of Female")
      sc.register(totalPointFAcc, "Total Point of Female")

      val avgGender = computeGenderAvg(
        questionnaireRDD,
        numMAcc,
        totalPointMAcc,
        numFAcc,
        totalPointFAcc
      )

      println(s"AVG ALL : $avgAll")
      avgAgeRange.foreach {
        case (ageRange, avg) => println(s"AVG Age Range($ageRange) : $avg")
      }

      avgGender.foreach {
        case (gender, avg) => println(s"AVG $gender : $avg")
      }
    } finally {
      sc.stop()
    }
  }
}
