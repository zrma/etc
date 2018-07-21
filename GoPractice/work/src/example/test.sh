mkdir ./reports
go-acc -o ./reports/coverage.out ./...
go test ./... -json > ./reports/report.json
go vet ./... 2> ./reports/govet-report.out
gometalinter.v2 --deadline=300s --disable=dupl --linter='vet:go tool vet -printfuncs=Infof,Debugf,Warningf,Errorf:PATH:LINE:MESSAGE' ./... > ./reports/gometalinter-report.out
gocov test ./... | gocov-html > ./reports/coverage.html
