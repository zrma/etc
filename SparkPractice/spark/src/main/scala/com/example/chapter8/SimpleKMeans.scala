package com.example.chapter8

import org.apache.spark.mllib.clustering.KMeans
import org.apache.spark.mllib.linalg.Vectors
import org.apache.spark.sql.SparkSession

import scala.reflect.io.{Directory, File}


// 주어진 데이터를 K개의 군집(클러스터)로 묶는 알고리즘.
// 비지도 학습의 일종으로 레이블이 없는 데이터를 사용한다.
object SimpleKMeans {
  def main(args: Array[String]): Unit = {
    val ss = SparkSession
      .builder()
      .master("local[*]")
      .appName("K-Means")
      .getOrCreate()

    //noinspection SpellCheckingInspection
    val data = ss.sparkContext.textFile("data/chapter8/kmeans_data.txt")

    val parsedData = data
      .map {
        // dense : 밀집, sparse : 희소
        s => Vectors.dense(s.split(' ').map(_.toDouble))
      }
      .cache()

    val clusterCount = 2
    val iterationCount = 20
    val clusters = KMeans.train(parsedData, clusterCount, iterationCount)

    println(s"Cluster count : ${clusters.k}")
    println(s"Cluster centers : ${clusters.clusterCenters.mkString(",")}")

    val vec1 = Vectors.dense(0.3, 0.3, 0.3)
    println(s"${vec1.toString} predict : ${clusters.predict(vec1)}")
    val vec2 = Vectors.dense(8.0, 8.0, 8.0)
    println(s"${vec2.toString} predict : ${clusters.predict(vec2)}")

    parsedData.foreach(
      vec => println(s"${vec.toString} predict : ${clusters.predict(vec)}")
    )

    // 입력 벡터 집합과 소속 클러스터의 중심과의 오차 제곱 합(SSE)
    val withinSetSumOfSquaredErrors = clusters.computeCost(parsedData)
    println(s"Within Set Sum Of Squared Errors = $withinSetSumOfSquaredErrors")

    try {
      val directory = Directory(File("output/KMeans_Model"))
      directory.deleteRecursively()
    } finally {
      clusters.save(ss.sparkContext, "output/KMeans_Model")
    }
  }
}
