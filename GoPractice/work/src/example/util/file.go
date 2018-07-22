package util

import (
	"bufio"
	"bytes"
	"os"
)

// WriteFile 파일 쓰기 유틸성 함수
func WriteFile(buf *bytes.Buffer, fileName string) {
	file, err := os.Create(fileName)
	CheckError(err)
	defer func() {
		CheckError(file.Close())
	}()

	writer := bufio.NewWriter(file)
	_, err = writer.Write(buf.Bytes())
	CheckError(err)

	CheckError(writer.Flush())
}

// RemoveFile 파일 제거 유틸성 함수
func RemoveFile(fileName string) {
	CheckError(os.Remove(fileName))
}
