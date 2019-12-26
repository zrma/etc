package com.example.chapter7

import java.io.PrintStream
import java.net.ServerSocket

import scala.collection.mutable.ArrayBuffer
import scala.io.Source

case class SimpleFeedSenderConfig(hostname: String = "localhost",
                                  port: Int = 12345,
                                  interval: Int = 500,
                                  inputFile: String = "input")

object SimpleFeedSender {

  def main(args: Array[String]) {
    var params = new ArrayBuffer[String]()
    params ++= args
    if (args.length == 0) {
      params += "localhost"
      params += "12345"
      params += "500"
      params += "data/chapter7/UCI_HAR_Dataset/train/x_train.txt"
    }

    Parser.sender().parse(params.result(), SimpleFeedSenderConfig()) exists { config =>
      println("Start server")

      val server = new ServerSocket(config.port)
      while (true) {
        val s = server.accept()
        new Thread() {
          val out = new PrintStream(s.getOutputStream)

          override def run() {

            println("Start processing")

            lazy val dataSource = Source.fromFile(config.inputFile)

            try {
              for (line <- dataSource.getLines) {
                Thread.sleep(config.interval)

                if (out.checkError()) {
                  println("disconnected")
                  return
                }

                out.println(line)
                out.flush()
              }
            } finally {

              println("Stop processing")

              dataSource.close()
              out.close()
              s.close()
            }
          }
        }.start()
      }

      true
    }
  }
}
