package main

import (
	"archive/tar"
	"archive/zip"
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
		{"readme.txt", "This tarPhase contains some text files."},
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

func tarPhase() {
	tarFile := archiveTar()
	unarchiveTar(tarFile)
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

func unarchiveZip() {

}

func zipPhase() {

}
