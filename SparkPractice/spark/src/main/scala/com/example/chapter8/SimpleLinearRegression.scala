package com.example.chapter8

import org.apache.spark.mllib.feature.StandardScaler
import org.apache.spark.mllib.regression.{LabeledPoint, LinearRegressionWithSGD}
import org.apache.spark.mllib.linalg.Vectors
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
    val labeledPoints = selectedDataDF.map { row => LabeledPoint(row.getDouble(0), Vectors.dense(row.getDouble(1), row.getDouble(2), row.getDouble(3))) }
    val scaler = new StandardScaler(withMean = true, withStd = true).fit(labeledPoints.rdd.map(x => x.features))
    val scaledLabeledPoints = labeledPoints.map { x => LabeledPoint(x.label, scaler.transform(x.features)) }

    val iterCount = 20
    val linearRegressionModel = LinearRegressionWithSGD.train(scaledLabeledPoints.rdd, iterCount)

    val targetDataVector1 = Vectors.dense(15.0, 15.4, 1)
    val targetDataVector2 = Vectors.dense(20.0, 0, 0)

    val targetScaledDataVector1 = scaler.transform(targetDataVector1)
    val targetScaledDataVector2 = scaler.transform(targetDataVector2)

    println(linearRegressionModel.predict(targetScaledDataVector1))
    println(linearRegressionModel.predict(targetScaledDataVector2))

    println(linearRegressionModel.weights)
  }
}
