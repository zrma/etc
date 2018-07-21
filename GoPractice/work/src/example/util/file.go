package util

import (
	"bufio"
	"bytes"
	"os"
)

func WriteFile(buf *bytes.Buffer, fileName string) {
	file, err := os.Create(fileName)
	CheckError(err)
	defer file.Close()

	writer := bufio.NewWriter(file)
	writer.Write(buf.Bytes())

	writer.Flush()
}

func RemoveFile(fileName string) {
	CheckError(os.Remove(fileName))
}
