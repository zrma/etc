// main.go
package main // import "github.com/zrma/PolyGlot/GoPractice/work"

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