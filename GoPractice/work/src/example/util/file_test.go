package util

import (
	"bytes"
	"os"
	"strings"
	"testing"

	"github.com/stretchr/testify/assert"
)

func TestWriteFile(t *testing.T) {
	reader := strings.NewReader("Hello World!")

	buf := new(bytes.Buffer)
	buf.ReadFrom(reader)

	fileName := "test.txt"

	WriteFile(buf, fileName)
	_, err := os.Stat(fileName)
	assert.True(t, err == nil || os.IsExist(err), "file not created!", fileName)

	RemoveFile(fileName)
	_, err = os.Stat(fileName)
	assert.True(t, os.IsNotExist(err), "file not created!", fileName)
}
