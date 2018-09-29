package com.example.chapter5

import java.io.{BufferedReader, InputStreamReader, Reader}

import org.apache.hadoop.conf.Configuration
import org.apache.hadoop.fs.{FileSystem, Path}
import org.apache.spark.broadcast.Broadcast
import org.apache.spark.rdd.RDD
import org.apache.spark.{SparkConf, SparkContext}

import scala.collection.mutable

object BestSellerFinder {
  private def createSaleRDD(csvFile: String, sc: SparkContext) = {
    val logRDD = sc.textFile(csvFile)
    logRDD.map(record => {
      val splitRecord = record.split(",")
      val productId = splitRecord(2)
      val numOfSold = splitRecord(3).toInt
      (productId, numOfSold)
    })
  }

  private def createOver10SoldRDD(rdd: RDD[(String, Int)]) = {
    rdd.reduceByKey(_ + _).filter(_._2 >= 10)
  }

  private def loadCSVIntoMap(productsCSVFile: String) = {
    val productsCSVReader: Reader = null

    try {
      val productsMap = new mutable.HashMap[String, (String, Int)]
      val hadoopConf = new Configuration
      val fs = FileSystem.get(hadoopConf)
      val is = fs.open(new Path(productsCSVFile))
      val productsCSVReader = new BufferedReader(new InputStreamReader(is))
      var line = productsCSVReader.readLine()

      while (line != null) {
        val splitLine = line.split(",")
        val productId = splitLine(0)
        val productName = splitLine(1)
        val unitPrice = splitLine(2).toInt
        productsMap(productId) = (productName, unitPrice)
        line = productsCSVReader.readLine()
      }

      productsMap
    } finally {
      if (productsCSVReader != null) {
        productsCSVReader.close()
      }
    }
  }

  private def createResultRDD(
    broadcastedMap: Broadcast[_ <: mutable.Map[String, (String, Int)]],
    rdd: RDD[(String, Int)]
  ) = {
    rdd.map {
      case (productId, amount) =>
        val productsMap = broadcastedMap.value
        val (productName, unitPrice) = productsMap(productId)
        (productName, amount, amount * unitPrice)
    }
  }

  def main(args: Array[String]): Unit = {
    require(args.length >= 4, """
              |args1 : <첫번째 달의 판매 데이터 파일 경로>
              |args2 : <두번째 달의 판매 데이터 파일 경로>
              |args3 : <상품의 마스터 데이터 파일 경로>
              |args4 : <출력 파일 경로>를 지정해주세요
              |""".stripMargin)

    val conf = new SparkConf()
      .setAppName("BestSellerFinder")
      .setMaster("local")
      .set("spark.serializer", "org.apache.spark.serializer.KryoSerializer")
    val sc = new SparkContext(conf)

    try {
      val Array(salesCSVFile1, salesCSVFile2, productsCSVFile, outputPath) =
        args.take(4)

      val salesRDD1 = createSaleRDD(salesCSVFile1, sc)
      val salesRDD2 = createSaleRDD(salesCSVFile2, sc)

      val over10SoldRDD1 = createOver10SoldRDD(salesRDD1)
      val over10SoldRDD2 = createOver10SoldRDD(salesRDD2)

      val bothOver10SoldRDD = over10SoldRDD1.join(over10SoldRDD2)
      val over10SoldAndAmountRDD = bothOver10SoldRDD.map {
        case (productId, (amount1, amount2)) =>
          (productId, amount1 + amount2)
      }

      val productMap = loadCSVIntoMap(productsCSVFile)
      val broadcastedMap = sc.broadcast(productMap)

      val resultRDD = createResultRDD(broadcastedMap, over10SoldAndAmountRDD)
      resultRDD.saveAsTextFile(outputPath)
    } finally {
      sc.stop()
    }
  }

}
