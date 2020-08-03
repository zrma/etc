package main

import (
	"context"
	"fmt"
	"log"
	"sync"
	"time"

	"github.com/streadway/amqp"

	"PolyGlot/RabbitMQPractice/pkg/mq"
)

func main() {
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()

	opt := mq.Option{
		Host:     "localhost",
		Port:     5672,
		Id:       "example",
		Password: "example",
	}
	client, err := mq.New(opt)
	if err != nil {
		log.Fatalln(err)
	}
	defer client.Close()

	var wg sync.WaitGroup
	wg.Add(2)
	go func() {
		send(cancel, client)
		wg.Done()
	}()
	go func() {
		receive(ctx, client)
		wg.Done()
	}()
	wg.Wait()
}

func receive(ctx context.Context, client *mq.Wrapper) {
	ch := client.Chan

	q, err := ch.QueueDeclare(
		"hello", // name
		false,   // durable
		false,   // delete when unused
		false,   // exclusive
		false,   // no-wait
		nil,     // arguments
	)
	failOnError(err, "Failed to declare a queue")

	messages, err := ch.Consume(
		q.Name, // queue
		"",     // consumer
		true,   // auto-ack
		false,  // exclusive
		false,  // no-local
		false,  // no-wait
		nil,    // args
	)
	failOnError(err, "Failed to register a consumer")

	for ctx.Err() == nil {
		select {
		case <-ctx.Done():
			break
		case msg := <-messages:
			log.Printf("Received a message: %s", msg.Body)
		}
	}
}

func send(cancel context.CancelFunc, client *mq.Wrapper) {
	defer cancel()

	ch := client.Chan

	q, err := ch.QueueDeclare(
		"hello", // name
		false,   // durable
		false,   // delete when unused
		false,   // exclusive
		false,   // no-wait
		nil,     // arguments
	)
	failOnError(err, "Failed to declare a queue")

	for i := 0; i < 10; i++ {
		body := fmt.Sprintln("Hello World! #(", i, ")")
		err = ch.Publish(
			"",     // exchange
			q.Name, // routing key
			false,  // mandatory
			false,  // immediate
			amqp.Publishing{
				ContentType: "text/plain",
				Body:        []byte(body),
			})
		failOnError(err, "Failed to publish a message")
		time.Sleep(500 * time.Millisecond)
	}
}

func failOnError(err error, msg string) {
	if err != nil {
		log.Fatalf("%s: %s", msg, err)
	}
}
