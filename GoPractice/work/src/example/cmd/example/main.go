package main

import (
	"log"

	"github.com/getsentry/raven-go"
)

func main() {

	if err := raven.SetDSN("https://e52a68c3b0314a45a9cd871bc6abe05c:0e4acc31f2d143b0ab4f2bad77cc2279@sentry.team504.co.kr/3"); err != nil {
		log.Panic(err)
	}
	defer raven.Close()
}
