package bufio

import (
	"bytes"
	"io"
	"strings"
)

func ExampleCustom() {
	Custom()
	// Output:
	// 1234
	// 5678
	// strconv.ParseInt: parsing "1234567901234567890": value out of range
	// strconv.ParseInt: parsing "1234567901234567890": value out of range
}

func ExampleEmptyFinalToken() {
	EmptyFinalToken()
	// Output:
	// "1" "2" "3" "4" ""
}

func ExampleLines() {
	r := strings.NewReader("Hello World!")
	buf := new(bytes.Buffer)
	reader := io.TeeReader(r, buf)

	Lines(&reader)
	Lines(nil)
	// Output:
	// Hello World!
}
