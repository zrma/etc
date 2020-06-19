FROM ubuntu:20.04

COPY etc/sources.list /etc/apt/

ARG DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \ 
    apt-get install --no-install-recommends \
        apt-utils=2.0.2ubuntu0.1 -y && \
    rm -fr /var/lib/apt/lists/*

RUN apt-get update && \
    apt-get install --no-install-recommends \
        telnet=0.17-41.2build1 \
        curl=7.68.0-1ubuntu2 -y && \
    rm -fr /var/lib/apt/lists/*

