defmodule PhoenixDocker.PageController do
  use PhoenixDocker.Web, :controller

  def index(conn, _params) do
    render conn, "index.html"
  end
end
