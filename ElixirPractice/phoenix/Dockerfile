FROM elixir:latest

RUN apt update -y
RUN apt upgrade -y

RUN apt install mariadb-client-10.1 -y

RUN mix local.hex --force
RUN mix archive.install --force https://github.com/phoenixframework/archives/raw/master/phoenix_new.ez
RUN mix local.rebar --force

WORKDIR /app
