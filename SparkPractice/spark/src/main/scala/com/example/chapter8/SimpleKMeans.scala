package com.example.chapter8

import org.apache.spark.ml.clustering.KMeans
import org.apache.spark.ml.evaluation.ClusteringEvaluator
import org.apache.spark.ml.feature.VectorAssembler
import org.apache.spark.sql.{Encoders, SparkSession}

import scala.reflect.io.{Directory, File}

case class Point(x: Double, y: Double, z: Double)

// 주어진 데이터를 K개의 군집(클러스터)로 묶는 알고리즘.
// 비지도 학습의 일종으로 레이블이 없는 데이터를 사용한다.
object SimpleKMeans {
  def main(args: Array[String]): Unit = {
    val ss = SparkSession
      .builder()
      .master("local[*]")
      .appName("K-Means")
      .getOrCreate()
    try {
      val dataEncoder = Encoders.product[Point]
      val ds = ss.read.schema(dataEncoder.schema).csv("data/chapter8/kmeans_data.csv").as[Point](dataEncoder)

      ds.printSchema()
      ds.show(3)

      val assembler = new VectorAssembler().setInputCols(Array("x", "y", "z")).setOutputCol("features")
      val df = assembler.transform(ds)

      df.printSchema()
      df.show(3)

      val clusterCount = 2
      val iterationCount = 20
      val kMeans = new KMeans().setK(clusterCount).setInitSteps(iterationCount)
      val model = kMeans.fit(df)

      println(s"Cluster count : ${model.k}")
      println(s"Cluster centers : ${model.clusterCenters.mkString(",")}")
      // Shows the result.
      println("Cluster Centers: ")
      model.clusterCenters.foreach(println)

      val predictions = model.transform(df)
      predictions.foreach(
        vec => println(s"${vec.toString}")
      )

      val evaluator = new ClusteringEvaluator()
      val silhouette = evaluator.evaluate(predictions)
      println(s"Silhouette with squared euclidean distance = $silhouette")

      import ss.implicits._
      val ds2 = ss.sqlContext.createDataset(Array(
        Point(0.3, 0.3, 0.3),
        Point(8.0, 8.0, 8.0)
      ))
      val df2 = assembler.transform(ds2)
      model.transform(df2).foreach(
        vec => println(s"${vec.toString}")
      )

      try {
        val directory = Directory(File("output/KMeans_Model/new"))
        directory.deleteRecursively()
      } finally {
        kMeans.save("output/KMeans_Model/new")
      }
    } finally {
      ss.stop()
    }
  }
}
