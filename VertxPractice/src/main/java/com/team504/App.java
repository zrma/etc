package com.team504;

import io.vertx.core.Vertx;

/**
 * Created by zrma on 2017. 2. 26..
 */
public class App {
    public static void main(String[] args) {
        // Create an HTTP server which simply returns "Hello World!" to each request.
        Vertx.vertx()
                .createHttpServer()
                .requestHandler(req -> req.response().end("Vertx.io!!"))
                .listen(8888, handler -> {
                    if (handler.succeeded()) {
                        System.out.println("http://localhost:8888/");
                    } else {
                        System.err.println("Failed to listen on port 8888");
                    }
                });
    }
}
