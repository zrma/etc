FROM golang:1.26.5-alpine3.24 AS builder
WORKDIR /src
COPY main.go .
RUN go build -o /app main.go

FROM alpine:3.24.1
ENV GOTRACEBACK=single
COPY --from=builder /app /app
CMD ["/app"]
