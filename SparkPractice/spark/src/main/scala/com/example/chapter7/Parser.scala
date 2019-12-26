package com.example.chapter7

object Parser {
  def receiver() = {
    new scopt.OptionParser[SimpleReceiverConfig]("SimpleFeedReceiver") {
      arg[String]("hostname") required() action { (x, c) =>
        c.copy(hostname = x)
      } text "The hostname to accept connections from remote hosts"

      arg[Int]("port") required() action { (x, c) => c.copy(port = x)
      } text "The port number to accept connections from remote hosts"

      arg[Int]("interval") required() action { (x, c) => c.copy(interval = x)
      } text "The interval to process data [msec]"
    }
  }

  def sender() = {
    new scopt.OptionParser[SimpleFeedSenderConfig]("SimpleFeedActor") {
      arg[String]("hostname") required() action { (x, c) =>
        c.copy(hostname = x)
      } text "The hostname to accept connections from remote hosts"

      arg[Int]("port") required() action { (x, c) => c.copy(port = x)
      } text "The port number to accept connections from remote hosts"

      arg[Int]("interval") required() action { (x, c) => c.copy(interval = x)
      } text "The interval to send messages to remote hosts [msec]"

      arg[String]("inputFile") required() action { (x, c) =>
        c.copy(inputFile = x)
      } text "The path of the input file"
    }
  }
}
