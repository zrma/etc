package com.example.chapter7

import java.io.PrintStream
import java.net.ServerSocket

import scala.io.Source

case class SimpleFeedSenderConfig(hostname: String = "localhost",
                                  port: Int = 12345,
                                  interval: Int = 500,
                                  inputFile: String = "input")

object SimpleFeedSender {

  def main(args: Array[String]) {
    val parser =
      new scopt.OptionParser[SimpleFeedSenderConfig]("SimpleFeedActor") {
        arg[String]("hostname") required () action { (x, c) =>
          c.copy(hostname = x)
        } text "The hostname to accept connections from remote hosts"

        arg[Int]("port") required () action { (x, c) => c.copy(port = x)
        } text "The port number to accept connections from remote hosts"

        arg[Int]("interval") required () action { (x, c) => c.copy(interval = x)
        } text "The interval to send messages to remote hosts [msec]"

        arg[String]("inputFile") required () action { (x, c) =>
          c.copy(inputFile = x)
        } text "The path of the input file"

      }

    parser.parse(args, SimpleFeedSenderConfig()) exists { config =>
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
