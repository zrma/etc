package main

import (
	"log"

	"github.com/getsentry/raven-go"
)

func main() {

	if err := raven.SetDSN(""); err != nil {
		log.Panic(err)
	}
	defer raven.Close()
}
