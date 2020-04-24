defmodule HelloElixir do
  @moduledoc """
  Documentation for `HelloElixir`.
  """

  @doc """
  Hello world.

  ## Examples

      iex> HelloElixir.hello()
      :world

  """
  def start do
    hello(System.argv())
  end

  def hello, do: IO.puts :world
  def hello(name), do: IO.puts "Hello, #{name}"
end
