defmodule CrawlTest do
  use ExUnit.Case
  doctest Crawl

  test "greets the world" do
    assert Crawl.hello() == :world
  end
end
