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
  def hello do
    :world
  end

  def pipe do
    "Elixir rocks"
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
