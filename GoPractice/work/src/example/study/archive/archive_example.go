package archive

import (
	"archive/tar"
	"archive/zip"
	"bufio"
	"bytes"
	"compress/flate"
	"fmt"
	"io"
	"io/ioutil"
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

func Tar() *bytes.Buffer {
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

func UnTar(buf *bytes.Buffer) {
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

func Zip() *bytes.Buffer {
	buf := new(bytes.Buffer)
	zipWriter := zip.NewWriter(buf)

	zipWriter.RegisterCompressor(zip.Deflate, func(out io.Writer) (io.WriteCloser, error) {
		return flate.NewWriter(out, flate.BestCompression)
	})

	files := buildSampleFiles()

	for _, file := range files {
		zipFile, err := zipWriter.Create(file.Name)
		util.CheckError(err)

		util.CheckError(zipFile.Write([]byte(file.Body)))
	}

	util.CheckError(zipWriter.Close())
	return buf
}

func UnZip(fileName string) {
	zipReader, err := zip.OpenReader(fileName)
	util.CheckError(err)
	defer zipReader.Close()

	for _, zipFile := range zipReader.File {
		fmt.Printf("Contents of %s :\n", zipFile.Name)

		readFile, err := zipFile.Open()
		util.CheckError(err)

		buf := bufio.NewReader(readFile)
		content, err := ioutil.ReadAll(buf)
		util.CheckError(err)

		fmt.Printf("%s", content)

		readFile.Close()
		fmt.Println()
	}
}
