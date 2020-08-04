package main

import (
	"context"
	"fmt"
	"log"
	"strings"
	"sync"
	"time"

	"github.com/divan/num2words"
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
	wg.Add(1)
	go func() {
		pub(cancel, client)
		wg.Done()
	}()

	const workCount = 5
	wg.Add(workCount)
	for i := 0; i < workCount; i++ {
		go func(idx int) {
			sub(ctx, client, idx)
			wg.Done()
		}(i)
	}
	wg.Wait()
}

func sub(ctx context.Context, client *mq.Wrapper, i int) {
	ch := client.Chan

	//goland:noinspection SpellCheckingInspection
	err := ch.ExchangeDeclare(
		"logs",   // name
		"fanout", // type
		true,     // durable
		false,    // auto-deleted
		false,    // internal
		false,    // no-wait
		nil,      // arguments
	)
	failOnError(err, "Failed to declare an exchange")

	q, err := ch.QueueDeclare(
		"",    // name
		false, // durable
		false, // delete when unused
		true,  // exclusive
		false, // no-wait
		nil,   // arguments
	)
	failOnError(err, "Failed to declare a queue")

	err = ch.QueueBind(
		q.Name, // queue name
		"",     // routing key
		"logs", // exchange
		false,
		nil,
	)
	failOnError(err, "Failed to bind a queue")

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
		case message := <-messages:
			log.Printf(" [%d] %s", i, message.Body)
		}
	}
}

func pub(cancel context.CancelFunc, client *mq.Wrapper) {
	defer cancel()

	ch := client.Chan

	//goland:noinspection SpellCheckingInspection
	err := ch.ExchangeDeclare(
		"logs",   // name
		"fanout", // type
		true,     // durable
		false,    // auto-deleted
		false,    // internal
		false,    // no-wait
		nil,      // arguments
	)
	failOnError(err, "Failed to declare an exchange")

	for i := 0; i < 10; i++ {
		dot := strings.Repeat(".", i)
		body := fmt.Sprintf("message: %s%s", num2words.Convert(i), dot)
		err = ch.Publish(
			"logs", // exchange
			"",     // routing key
			false,  // mandatory
			false,  // immediate
			amqp.Publishing{
				ContentType: "text/plain",
				Body:        []byte(body),
			})
		failOnError(err, "Failed to publish a message")
		time.Sleep(time.Second)
	}
}

func failOnError(err error, msg string) {
	if err != nil {
		log.Fatalf("%s: %s", msg, err)
	}
}
