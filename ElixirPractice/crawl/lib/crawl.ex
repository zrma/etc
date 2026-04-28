defmodule Crawl do
  @moduledoc """
  Documentation for Crawl.
  """

  @doc """
  Hello world.

  ## Examples

      iex> Crawl.hello
      :world

  """
  def hello, do: :world
  def hello(name) when is_binary(name), do: name
  def hello(name) when is_list(name), do: Enum.join(name, ",")

  def pipe(input) do
    input
    |> String.split()
    |> Enum.map(
      &(&1
        |> String.upcase())
    )
    |> Enum.each(
      &(&1
        |> IO.puts())
    )
  end
end
