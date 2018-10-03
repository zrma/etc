package com.example.chapter8

import org.apache.spark.mllib.clustering.KMeans
import org.apache.spark.mllib.linalg.Vectors
import org.apache.spark.sql.SparkSession

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

    // 입력 벡터 집합과 소속 클러스터의 중심과의 오차 제홉 합(SSE)
    val withinSetSumOfSquaredErrors = clusters.computeCost(parsedData)
    println(s"Within Set Sum Of Squared Errors = $withinSetSumOfSquaredErrors")

    clusters.save(ss.sparkContext, "output/KMeans_Model")
  }
}
