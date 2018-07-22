package util

import (
	"fmt"

	"github.com/getsentry/raven-go"
)

// CheckError 센트리 오류 보고
func CheckError(args ...interface{}) {
	raven.CapturePanicAndWait(func() {
		argsLen := len(args)
		lastToken := args[argsLen-1]
		if lastToken != nil {
			err := lastToken.(error)
			raven.CaptureError(err, nil)
			fmt.Println(err)
		}
	}, nil)
}
