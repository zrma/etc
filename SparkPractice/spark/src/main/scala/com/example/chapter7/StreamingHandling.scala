package com.example.chapter7

import org.apache.log4j.{Level, Logger}
import org.apache.spark.sql.SparkSession
import org.apache.spark.storage.StorageLevel
import org.apache.spark.streaming.dstream.InputDStream
import org.apache.spark.streaming.{Milliseconds, Seconds, StreamingContext}

object StreamingHandling {
  private def transform(lines: InputDStream[String]): Unit = {
    val splitLines = lines.map(_.trim).map(_.split("[\\s]+"))
    val dataArray = splitLines.map(_.take(3)).map(_.map(_.toDouble))

    // 일정 시간 간격의 윈도우로 잘라서 처리
    val dataArrayInWindow = dataArray.window(Milliseconds(2000))

    val abnormalityInWindow = dataArrayInWindow.transform { rdd =>
      val abnormality = if (rdd.isEmpty) {
        val arrayOfMax =
          Array(Double.MaxValue, Double.MaxValue, Double.MaxValue)
        val tmpIndex = Long.MaxValue
        rdd.sparkContext.parallelize(Array((arrayOfMax, tmpIndex)))
      } else {
        // 데이터 건수
        val count = rdd.count

        // 합계
        val sum = rdd.reduce { (a: Array[Double], b: Array[Double]) =>
          a.indices.map(i => a(i) + b(i)).toArray
        }

        // 평균
        val mean = sum.indices.map(i => sum(i) / count).toArray

        // 편차 제곱
        val deviation = rdd.map { p =>
          p.indices.map { i => scala.math.pow(p(i) - mean(i), 2)
          }.toArray
        }

        // 분산
        val variance = deviation
          .reduce { (a: Array[Double], b: Array[Double]) =>
            a.indices.map(i => a(i) + b(i)).toArray
          }
          .map(p => p / count)

        // 표준편차 = sqrt(분산)
        val stdDev = variance.map(p => scala.math.sqrt(p))

        val diffMeanWithIndex = rdd.zipWithIndex.map {
          case (values, index) =>
            val diffMean = values.indices.map { i =>
              math.abs(values(i) - mean(i))
            }.toArray
            (diffMean, index)
        }

        // 평균으로부터의 차이가 표준편차의 3배 이상이라면 이상값으로 판정
        val strange = diffMeanWithIndex.filter {
          case (values, _) =>
            values.indices.exists(i => values(i) > 3 * stdDev(i))
        }

        strange
      }

      abnormality.map {
        case (values, index) =>
          (values.mkString(","), index)
      }
    }

    abnormalityInWindow.print()
  }

  def main(args: Array[String]): Unit = {

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
      Logger.getRootLogger.setLevel(Level.WARN)

      val ss = SparkSession
        .builder()
        .master("local[*]")
        .appName("SparkStreaming")
        .getOrCreate()
      val ssc = new StreamingContext(ss.sparkContext, Seconds(2))

      val lines = ssc.socketTextStream(
        config.hostname,
        config.port,
        StorageLevel.MEMORY_AND_DISK_SER
      )
      transform(lines)

      ssc.start()
      ssc.awaitTermination()
      ssc.stop()

      true
    }
  }
}
