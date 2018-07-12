package archive

import (
	"archive/tar"
	"archive/zip"
	"bufio"
	"bytes"
	"fmt"
	"io"
	"os"

	"example/util"
)

type file struct {
	Name, Body string
}

func buildSampleFiles() []file {
	return []file{
		{"readme.txt", "This phase contains some text files."},
		{"gopher.txt", "Gopher name:\nGeorge\nGeoffrey\nGonzo"},
		{"note.txt", "Get animal handling license."},
	}
}

func archiveTar() *bytes.Buffer {
	var buf bytes.Buffer
	tarWriter := tar.NewWriter(&buf)

	files := buildSampleFiles()

	for _, file := range files {
		header := &tar.Header{
			Name: file.Name,
			Mode: 0600,
			Size: int64(len(file.Body)),
		}

		util.CheckError(tarWriter.WriteHeader(header))
		util.CheckError(tarWriter.Write([]byte(file.Body)))
	}

	util.CheckError(tarWriter.Close())

	return &buf
}

func unarchiveTar(buf *bytes.Buffer) {
	tarReader := tar.NewReader(buf)
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break
		}
		util.CheckError(err)

		fmt.Printf("Contents of %s :\n", header.Name)

		util.CheckError(io.Copy(os.Stdout, tarReader))

		fmt.Println()
	}
}

func TarPhase() {
	buffer := archiveTar()
	unarchiveTar(buffer)
}

func archiveZip() *bytes.Buffer {
	buf := new(bytes.Buffer)
	zipWriter := zip.NewWriter(buf)

	files := buildSampleFiles()

	for _, file := range files {
		zipFile, err := zipWriter.Create(file.Name)
		util.CheckError(err)

		util.CheckError(zipFile.Write([]byte(file.Body)))
	}

	util.CheckError(zipWriter.Close())
	return buf
}

func unarchiveZip(fileName string) {
	reader, err := zip.OpenReader(fileName)
	util.CheckError(err)
	defer reader.Close()

	for _, file := range reader.File {
		fmt.Printf("Contents of %s :\n", file.Name)

		rc, err := file.Open()
		util.CheckError(err)

		_, err = io.CopyN(os.Stdout, rc, 68)
		util.CheckError(err)

		rc.Close()
		fmt.Println()
	}
}

func ZipPhase() {
	fileName := "/tmp/test.zip"

	buffer := archiveZip()
	writeFile(buffer, fileName)
	unarchiveZip(fileName)
	removeFile(fileName)
}

func writeFile(buf *bytes.Buffer, fileName string) {
	file, err := os.Create(fileName)
	util.CheckError(err)
	defer file.Close()

	writer := bufio.NewWriter(file)
	writer.Write(buf.Bytes())

	writer.Flush()
}

func removeFile(fileName string) {
	util.CheckError(os.Remove(fileName))
}
