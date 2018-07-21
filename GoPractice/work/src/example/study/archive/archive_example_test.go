package archive

import "example/util"

func ExampleTarPhase() {
	buffer := Tar()
	UnTar(buffer)
	// Output:
	// Contents of readme.txt :
	// This phase contains some text files.
	// Contents of gopher.txt :
	// Gopher name:
	// George
	// Geoffrey
	// Gonzo
	// Contents of note.txt :
	// Get animal handling license.

}

func ExampleZipPhase() {
	fileName := "/tmp/test.zip"

	buffer := Zip()
	util.WriteFile(buffer, fileName)
	UnZip(fileName)
	util.RemoveFile(fileName)
	// Output:
	// Contents of readme.txt :
	// This phase contains some text files.
	// Contents of gopher.txt :
	// Gopher name:
	// George
	// Geoffrey
	// Gonzo
	// Contents of note.txt :
	// Get animal handling license.
}
