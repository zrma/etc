package main

import (
	"bytes"
	"context"
	"fmt"
	"log"
	"math/rand"
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
		createTask(cancel, client)
		wg.Done()
	}()

	const workCount = 3
	wg.Add(workCount)
	for i := 0; i < workCount; i++ {
		go func(idx int) {
			worker(ctx, client, idx)
			wg.Done()
		}(i)
	}
	wg.Wait()
}

func worker(ctx context.Context, client *mq.Wrapper, idx int) {
	ch := client.Chan

	q, err := ch.QueueDeclare(
		"task_queue", // name
		false,        // durable
		false,        // delete when unused
		false,        // exclusive
		false,        // no-wait
		nil,          // arguments
	)
	failOnError(err, "Failed to declare a queue")

	err = ch.Qos(
		1,     // prefetch count
		0,     // prefetch size
		false, // global
	)
	failOnError(err, "Failed to set QoS")

	messages, err := ch.Consume(
		q.Name, // queue
		"",     // consumer
		false,  // auto-ack
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
			msg := message.Body
			log.Printf("[#%d] Received a message: %s", idx, msg)
			dotCount := bytes.Count(msg, []byte("."))
			t := time.Duration(dotCount)
			time.Sleep(t * 100 * time.Millisecond)
			log.Printf("Done")

			if rand.Intn(10) == 7 {
				log.Printf("Ack failed: %s", msg)
			} else {
				message.Ack(false)
				log.Println("Ack succeeded")
			}
		}
	}
}

func createTask(cancel context.CancelFunc, client *mq.Wrapper) {
	defer cancel()

	ch := client.Chan

	q, err := ch.QueueDeclare(
		"task_queue", // name
		false,        // durable
		false,        // delete when unused
		false,        // exclusive
		false,        // no-wait
		nil,          // arguments
	)
	failOnError(err, "Failed to declare a queue")

	for i := 0; i < 10; i++ {
		dot := strings.Repeat(".", i)
		body := fmt.Sprintf("message: %s%s", num2words.Convert(i), dot)
		err = ch.Publish(
			"",     // exchange
			q.Name, // routing key
			false,  // mandatory
			false,
			amqp.Publishing{
				DeliveryMode: amqp.Persistent,
				ContentType:  "text/plain",
				Body:         []byte(body),
			})
		failOnError(err, "Failed to publish a message")
		log.Printf(" [x] Sent %s", body)
	}

	time.Sleep(60 * time.Second)
}

func failOnError(err error, msg string) {
	if err != nil {
		log.Fatalf("%s: %s", msg, err)
	}
}
