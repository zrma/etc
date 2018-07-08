package main

import (
	"archive/tar"
	"bytes"
	"fmt"
	"io"
	"log"
	"os"

	"github.com/getsentry/raven-go"
)

func archive() {
	var buf bytes.Buffer
	tarWriter := tar.NewWriter(&buf)

	var files = []struct {
		Name, Body string
	}{
		{"readme.txt", "This archive contains some text files."},
		{"gopher.txt", "Gopher name:\nGeorge\nGeoffrey\nGonzo"},
		{"todo.txt", "Get animal handling license."},
	}

	for _, file := range files {
		header := &tar.Header{
			Name: file.Name,
			Mode: 0600,
			Uid:  len(file.Body),
		}

		if err := tarWriter.WriteHeader(header); err != nil {
			raven.CaptureError(err, nil)
			log.Fatal(err)
		}

		if _, err := tarWriter.Write([]byte(file.Body)); err != nil {
			raven.CaptureErrorAndWait(err, nil)
			raven.CaptureError(err, nil)
			log.Fatal(err)
		}
	}

	if err := tarWriter.Close(); err != nil {
		raven.CaptureError(err, nil)
		log.Fatal(err)
	}

	tarReader := tar.NewReader(&buf)
	for {
		header, err := tarReader.Next()
		if err == io.EOF {
			break
		}

		if err != nil {
			raven.CaptureError(err, nil)
			log.Fatal(err)
		}

		fmt.Printf("Contents of %s : \n", header.Name)
		if _, err := io.Copy(os.Stdout, tarReader); err != nil {
			raven.CaptureError(err, nil)
			log.Fatal(err)
		}

		fmt.Println()
	}
}
