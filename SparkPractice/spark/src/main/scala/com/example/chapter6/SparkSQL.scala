package com.example.chapter6

import org.apache.spark.sql.SparkSession
import org.apache.spark.sql.expressions.UserDefinedAggregateFunction
import org.apache.spark.sql.functions._
import org.apache.spark.sql.types._
import org.apache.spark.sql.Row
import org.apache.spark.sql.expressions.MutableAggregationBuffer

import java.math.BigDecimal

//noinspection SpellCheckingInspection
case class Dessert(menuId: String, name: String, price: Int, kcal: Int)

case class DessertOrder(sId: String, menuId: String, num: Int)

class CustomSum extends UserDefinedAggregateFunction {

  import org.apache.spark.sql.types.StructField

  override def inputSchema: StructType =
    StructType(StructField("amount_per_slip", IntegerType) :: Nil)

  override def bufferSchema: StructType =
    StructType(StructField("sum", IntegerType) :: Nil)

  override def dataType: DataType = IntegerType

  override def deterministic: Boolean = true

  override def initialize(buffer: MutableAggregationBuffer): Unit = {
    buffer(0) = 0
  }

  override def update(buffer: MutableAggregationBuffer, input: Row): Unit = {
    buffer(0) = buffer.getAs[Int](0) + input.getAs[Int](0)
  }

  override def merge(buffer1: MutableAggregationBuffer, buffer2: Row): Unit = {
    buffer1(0) = buffer1.getAs[Int](0) + buffer2.getAs[Int](0)
  }

  override def evaluate(buffer: Row): Any = {
    buffer.getInt(0)
  }
}

case class DecimalTypeContainer(data: BigDecimal)

object SparkSQL {
  def main(args: Array[String]): Unit = {
    import org.apache.spark.sql.Encoders
    val warehouseLocation = "/Users/zrma/Documents/Code/PolyGlot/SparkPractice/spark/spark-warehouse"
    val ss = SparkSession
      .builder()
      .master("local[*]")
      .appName("SparkSQL")
      .config("spark.sql.warehouse.dir", warehouseLocation)
      .enableHiveSupport()
      .getOrCreate()

    val dessertEncoder = Encoders.product[Dessert]
    val dessertDS = ss.read
      .schema(dessertEncoder.schema)
      .csv("data/chapter6/dessert-menu.csv")
      .as[Dessert](dessertEncoder)

    val dessertDF = dessertDS.toDF()
    dessertDF.cache()
    dessertDF.createOrReplaceTempView("dessert_table")

    ss.sqlContext.cacheTable("dessert_table")

    //////////////////////////////////////////////////////////////////////////////////////////
    // Raw Query
    //////////////////////////////////////////////////////////////////////////////////////////
    val numOver300KcalDF = ss.sql(
      "SELECT count(*) AS num_of_over_300Kcal FROM dessert_table WHERE kcal >= 260"
    )
    numOver300KcalDF.show()

    // spark-sql 내장 함수
    ss.sql("SELECT atan2(1, 3) AS ATAN2_1_3").show()

    // spark-hive 내장 함수
    ss.sql("SELECT pi() AS PI, e() AS E").show()
    //////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////
    // Method Query
    //////////////////////////////////////////////////////////////////////////////////////////
    val nameAndPriceDF = dessertDF.select(dessertDF("name"), dessertDF("price"))
    nameAndPriceDF.printSchema()
    nameAndPriceDF.show()

    val selectAllDS = dessertDS.select("*")
    selectAllDS.show(3)

    // column $ alias
    import org.apache.spark.sql.SaveMode
    import ss.sqlContext.implicits._
    val nameAndDollarDF = nameAndPriceDF.select($"name", $"price" / lit(1000.0))
    nameAndDollarDF.show()

    val over5200WonDF = dessertDF.where($"price" >= 5200)
    over5200WonDF.show()

    val over5200WonNameDF = dessertDF.where($"price" >= 5200).select($"name")
    over5200WonNameDF.show()

    val sortedDessertDF = dessertDF.orderBy($"price".asc, $"kcal".desc)
    sortedDessertDF.show()

    // aggregate
    val avgKcalDF = dessertDF.agg(avg($"kcal") as "avg_of_kcal")
    avgKcalDF.show()

    val numPerPriceRangeDF = dessertDF
      .groupBy((($"price" / 1000) cast IntegerType) * 1000 as "price_range")
      .agg(count($"price"))
      .orderBy($"price_range")
    numPerPriceRangeDF.show()

    val dessertOrderEncoder = Encoders.product[DessertOrder]
    val dessertOrderDF = ss.read
      .schema(dessertOrderEncoder.schema)
      .csv("data/chapter6/dessert-order.csv")
      .as[DessertOrder](dessertOrderEncoder)
      .toDF()
    dessertOrderDF.cache()

    dessertOrderDF.createOrReplaceTempView("dessert_order_table")
    ss.sqlContext.cacheTable("dessert_order_table")

    // Join
    val amountPerMenuPerSlipDF = dessertDF
      .join(
        dessertOrderDF,
        dessertDF("menuId") === dessertOrderDF("menuId"),
        "inner"
      )
      .select(
        $"sId",
        $"name",
        ($"num" * $"price") as "amount_per_menu_per_slip"
      )
      .orderBy($"amount_per_menu_per_slip".desc)
    amountPerMenuPerSlipDF.show()

    val amountPerSlipDF = amountPerMenuPerSlipDF
      .groupBy($"sId")
      .agg(sum($"amount_per_menu_per_slip") as "amount_per_slip")
      .select($"sId", $"amount_per_slip")
    amountPerSlipDF.show()
    //////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////
    // UDF(User Defined Function)
    //////////////////////////////////////////////////////////////////////////////////////////
    val strlen = ss.udf.register("strlen", (str: String) => str.length)
    ss.sql("SELECT strlen('Hello Spark SQL') AS result_of_strlen").show()

    // DataFrame API에서만 UDF를 사용할 때는 udf() 함수를 이용할 수 있다.
    // udf() 함수는 org.apache.spark.sql.functions._ 을 임포트 해야 한다.
    val strlen2 = udf((str: String) => str.length)
    amountPerSlipDF.withColumn("length", length($"sId")).show

    val customSum = new CustomSum()
    amountPerSlipDF.agg(customSum($"amount_per_slip")).show()

    amountPerSlipDF.agg(sum($"amount_per_slip")).show()

    val dummyDF = ss.sparkContext.parallelize(1 to 1).toDF()
    dummyDF
      .select(callUDF("strlen", lit("Hello UDF")) as "result_of_strlen")
      .show()

    dummyDF.select(callUDF("pi") as "PI", callUDF("e") as "E").show()
    //////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////
    // Structed DataSet
    //////////////////////////////////////////////////////////////////////////////////////////
    val dfWriter = dessertDF.write
    dfWriter
      .format("parquet")
      .mode(SaveMode.Overwrite)
      .save("output/dessert_parquet")

    val dfReader = ss.read
    val dessertDF2 = dfReader.format("parquet").load("output/dessert_parquet")
    dessertDF2.orderBy($"name").show(3)

    dessertDF.write
      .format("parquet")
      .mode(SaveMode.Overwrite)
      .saveAsTable("dessert_tbl_parquet")
    ss.read.format("parquet").table("dessert_tbl_parquet").show(3)
    ss.sql("SELECT * FROM dessert_tbl_parquet LIMIT 3").show()

    val bdContainerDF = ss.sparkContext
      .parallelize(List(new BigDecimal("12345.67890123456789123456")))
      .map(data => DecimalTypeContainer(data))
      .toDF()
    bdContainerDF.printSchema()
    bdContainerDF.show()

    // data 문자열의 길이가 20글자를 넘을 경우에도 생략하지 않고 출력
    bdContainerDF.show(false)

    bdContainerDF.write
      .format("orc")
      .mode(SaveMode.Overwrite)
      .save("output/bdContainerORC")
    val bdContainerORCDF = ss.read.format("orc").load("output/bdContainerORC")
    bdContainerORCDF.printSchema()
    bdContainerORCDF.show()
    bdContainerORCDF.show(false)

    bdContainerDF.write
      .format("json")
      .mode(SaveMode.Overwrite)
      .save("output/bdContainerJSON")
    var bdContainerJSONDF =
      ss.read.format("json").load("output/bdContainerJSON")
    bdContainerJSONDF.printSchema()
    bdContainerJSONDF.show()
    bdContainerJSONDF.show(false)

    // 스키마 명시적으로 지정
    val explicitScheme = DataTypes.createStructType(
      Array(
        DataTypes
          .createStructField("data", DataTypes.createDecimalType(38, 18), true)
      )
    )
    bdContainerJSONDF = ss.read
      .schema(explicitScheme)
      .format("json")
      .load("output/bdContainerJSON")
    bdContainerJSONDF.printSchema()
    bdContainerJSONDF.show()
    bdContainerJSONDF.show(false)
    //////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////
    // 파티셔닝
    //////////////////////////////////////////////////////////////////////////////////////////
    val priceRangeDessertDF = dessertDF.select(
      ((($"price" / 1000) cast IntegerType) * 1000) as "price_range",
      dessertDF("*")
    )
    priceRangeDessertDF.write
      .format("parquet")
      .mode(SaveMode.Overwrite)
      .save("output/price_range_dessert_parquet_non_partitioned")
    priceRangeDessertDF.write
      .format("parquet")
      .mode(SaveMode.Overwrite)
      .partitionBy("price_range")
      .save("output/price_range_dessert_parquet_partitioned")

    val nonPartitionedDessertDF = ss.read
      .format("parquet")
      .load("output/price_range_dessert_parquet_non_partitioned")
    nonPartitionedDessertDF.where($"price_range" >= 5000).explain()

    val partitionedDessertDF = ss.read
      .format("parquet")
      .load("output/price_range_dessert_parquet_partitioned")
    partitionedDessertDF.where($"price_range" >= 5000).explain()
    //////////////////////////////////////////////////////////////////////////////////////////

    dessertDF.unpersist()
    dessertOrderDF.unpersist()
    ss.sqlContext.uncacheTable("dessert_table")
    ss.sqlContext.uncacheTable("dessert_order_table")
  }
}
