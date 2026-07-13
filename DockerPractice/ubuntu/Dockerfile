FROM ubuntu:26.04

ARG DEBIAN_FRONTEND=noninteractive

# hadolint ignore=DL3008
RUN apt-get update && \
    apt-get install --no-install-recommends -y \
        apt-utils \
        curl \
        inetutils-telnet && \
    rm -fr /var/lib/apt/lists/*
