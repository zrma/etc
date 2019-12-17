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
  def hello(name) do
    cond do
      String.valid?(name) ->
        name
      Kernel.is_list(name) ->
        name
        |> Enum.join(",")
    end
  end

  def pipe(input) do
    input
    |> String.split()
    |> Enum.map(
         &(
           &1
           |> String.upcase)
       )
    |> Enum.each(
         &(
           &1
           |> IO.puts)
       )
  end
end
