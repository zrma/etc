FROM golang:1.16.5-alpine3.13 as builder
COPY main.go .
RUN go build -o /app main.go

FROM alpine:3.13.5
ENV GOTRACEBACK=single
CMD ["./app"]
COPY --from=builder /app .
