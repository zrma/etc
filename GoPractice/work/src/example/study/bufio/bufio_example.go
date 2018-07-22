package bufio

import (
	"bufio"
	"fmt"
	"io"
	"os"
	"strconv"
	"strings"

	"example/util"
)

// Custom Split 연습
func Custom() {
	const input = "1234 5678 1234567901234567890"

	scanner := bufio.NewScanner(strings.NewReader(input))
	split := func(data []byte, atEOF bool) (advance int, token []byte, err error) {
		advance, token, err = bufio.ScanWords(data, atEOF)
		if err == nil && token != nil {
			_, err = strconv.ParseInt(string(token), 10, 32)
			util.CheckError(err)

			return
		}

		return
	}

	scanner.Split(split)

	for scanner.Scan() {
		fmt.Printf("%s\n", scanner.Text())
	}

	util.CheckError(scanner.Err())
}

// EmptyFinalToken Custom Split 연습 Comma 버전
func EmptyFinalToken() {
	const input = "1,2,3,4,"

	scanner := bufio.NewScanner(strings.NewReader(input))
	onComma := func(data []byte, _ bool) (advance int, token []byte, err error) {
		for i := 0; i < len(data); i++ {
			if data[i] == ',' {
				return i + 1, data[:i], nil
			}
		}

		return 0, data, bufio.ErrFinalToken
	}

	scanner.Split(onComma)

	for scanner.Scan() {
		fmt.Printf("%q ", scanner.Text())
	}

	util.CheckError(scanner.Err())
}

// Lines os.Stdin나 기타 io.Reader를 통한 여러 줄 scan 연습
func Lines(reader *io.Reader) {
	var scanner *bufio.Scanner
	if reader == nil {
		scanner = bufio.NewScanner(os.Stdin)
	} else {
		scanner = bufio.NewScanner(*reader)
	}
	for scanner.Scan() {
		fmt.Println(scanner.Text())
	}

	util.CheckError(scanner.Err())
}
