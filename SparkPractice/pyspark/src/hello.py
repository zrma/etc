from typing import Any, Tuple

from pyspark import SparkContext, RDD

if __name__ == "__main__":
    sc: SparkContext = SparkContext(master="local", appName="Hello World")

    logFile: str = "../README.md"
    logData: RDD = sc.textFile(logFile, 2).cache()

    lineCount: Tuple[Any, ...] = logData.count()
    print(lineCount)

    sc.stop()
