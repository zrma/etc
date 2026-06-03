package mq

import (
	"errors"
	"fmt"
	"os"
	"strconv"

	amqp "github.com/rabbitmq/amqp091-go"
)

func New(option Option) (*Wrapper, error) {
	endpoint := fmt.Sprintf(
		"amqp://%s:%s@%s:%d/",
		option.Id, option.Password, option.Host, option.Port,
	)
	conn, err := amqp.Dial(endpoint)
	if err != nil {
		return nil, errMsg(err, "Failed to connect to RabbitMQ")
	}

	ch, err := conn.Channel()
	if err != nil {
		conn.Close()
		return nil, errMsg(err, "Failed to open a channel")
	}

	return &Wrapper{Conn: conn, Chan: ch}, nil
}

func errMsg(err error, msg string) error {
	return errors.New(fmt.Sprintf("%s: %s", msg, err))
}

func OptionFromEnv() (Option, error) {
	user, err := requiredEnv("RABBITMQ_USER")
	if err != nil {
		return Option{}, err
	}
	password, err := requiredEnv("RABBITMQ_PASSWORD")
	if err != nil {
		return Option{}, err
	}
	port, err := intEnv("RABBITMQ_PORT", 5672)
	if err != nil {
		return Option{}, err
	}
	return Option{
		Host:     stringEnv("RABBITMQ_HOST", "localhost"),
		Port:     port,
		Id:       user,
		Password: password,
	}, nil
}

func requiredEnv(name string) (string, error) {
	value := os.Getenv(name)
	if value == "" {
		return "", fmt.Errorf("%s is required", name)
	}
	return value, nil
}

func stringEnv(name string, fallback string) string {
	value := os.Getenv(name)
	if value == "" {
		return fallback
	}
	return value
}

func intEnv(name string, fallback int) (int, error) {
	value := os.Getenv(name)
	if value == "" {
		return fallback, nil
	}
	parsed, err := strconv.Atoi(value)
	if err != nil {
		return 0, fmt.Errorf("%s must be an integer: %w", name, err)
	}
	return parsed, nil
}

type Option struct {
	Host     string
	Port     int
	Id       string
	Password string
}

type Wrapper struct {
	Conn *amqp.Connection
	Chan *amqp.Channel
}

func (w *Wrapper) Close() {
	if w.Chan != nil {
		w.Chan.Close()
		w.Chan = nil
	}
	if w.Conn != nil {
		w.Conn.Close()
		w.Conn = nil
	}
}
