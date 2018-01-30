defmodule Example do
  use Application
  require Logger

  def start(_type, _args) do
    port = Application.get_env(:concoction, :cowboy_port, 8080)

        children = [
          Plug.Adapters.Cowboy.child_spec(:http, Example.Router, [], port: port)
        ]

    Logger.info("Started application")
	Supervisor.start_link(children, strategy: :one_for_one)
  end

  def init(options) do
    options
  end

  def call(conn, _opts) do
    Plug.Conn.send_resp(conn, 200, "Hello, Elixir!")
  end
end
