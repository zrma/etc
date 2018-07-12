go test -coverprofile=coverage.out ./...
go vet 2> govet-report.out ./...
gometalinter.v2 --linter='vet:go tool vet -printfuncs=Infof,Debugf,Warningf,Errorf:PATH:LINE:MESSAGE' ./... > gometalinter-report.out
go test -json > report.json ./...