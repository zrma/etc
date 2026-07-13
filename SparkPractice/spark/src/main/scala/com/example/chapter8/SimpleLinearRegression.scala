package com.example.chapter8

import org.apache.spark.ml.feature.VectorAssembler
import org.apache.spark.ml.linalg.Vectors
import org.apache.spark.ml.regression.LinearRegression
import org.apache.spark.sql.SparkSession
import org.apache.spark.sql.Encoders
import org.apache.spark.sql.functions._

case class Weather(date: String,
                   day_of_week: String,
                   avg_temp: Double,
                   max_temp: Double,
                   min_temp: Double,
                   rainfall: Double,
                   daylight_hours: Double,
                   max_depth_snowfall: Double,
                   total_snowfall: Double,
                   solar_radiation: Double,
                   mean_wind_speed: Double,
                   max_wind_speed: Double,
                   max_instantaneous_wind_speed: Double,
                   avg_humidity: Double,
                   avg_cloud_cover: Double)

case class Sales(date: String, sales: Double)

object SimpleLinearRegression {

  def main(args: Array[String]): Unit = {

    val ss = SparkSession
      .builder()
      .master("local[*]")
      .appName("LinearRegression")
      .getOrCreate()

    val weatherEncoder = Encoders.product[Weather]
    val weatherDF = ss.read
      .schema(weatherEncoder.schema)
      .csv("data/chapter8/weather.csv")
      .as[Weather](weatherEncoder)
      .toDF()

    val salesEncoder = Encoders.product[Sales]
    val salesDF = ss.read
      .schema(salesEncoder.schema)
      .csv("data/chapter8/sales.csv")
      .as[Sales](salesEncoder)
      .toDF()

    weatherDF.printSchema()
    salesDF.printSchema()

    val salesAndWeatherDF = salesDF.join(weatherDF, "date")
    salesAndWeatherDF.show(5)

    val isWeekend = udf(
      (t: String) =>
        t match {
          case x if x.contains("日") => 1d
          case x if x.contains("土") => 1d
          case _ => 0d
        }
    )

    val replacedSalesAndWeatherDF = salesAndWeatherDF
      .withColumn("weekend", isWeekend(salesAndWeatherDF("day_of_week")))
      .drop("day_of_week")

    replacedSalesAndWeatherDF.show(5)

    val selectedDataDF = replacedSalesAndWeatherDF.select("sales", "avg_temp", "rainfall", "weekend")

    import ss.implicits._
    val assembler = new VectorAssembler()
      .setInputCols(Array("avg_temp", "rainfall", "weekend"))
      .setOutputCol("features")
    val trainingData = assembler
      .transform(selectedDataDF)
      .select(col("sales").as("label"), col("features"))

    val iterCount = 20
    val linearRegressionModel = new LinearRegression()
      .setMaxIter(iterCount)
      .fit(trainingData)

    val targetDataVector1 = Vectors.dense(15.0, 15.4, 1)
    val targetDataVector2 = Vectors.dense(20.0, 0, 0)

    println(linearRegressionModel.predict(targetDataVector1))
    println(linearRegressionModel.predict(targetDataVector2))

    println(linearRegressionModel.coefficients)
  }
}
