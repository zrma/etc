package util

import (
	"log"

	"github.com/getsentry/raven-go"
)

func CheckError(args ...interface{}) {
	raven.CapturePanicAndWait(func() {
		argsLen := len(args)
		lastToken := args[argsLen]
		if lastToken != nil {
			err := lastToken.(error)
			raven.CaptureError(err, nil)
			log.Fatal(err)
		}
	}, nil)
}
