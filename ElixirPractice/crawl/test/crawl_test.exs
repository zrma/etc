defmodule CrawlTest do
  use ExUnit.Case
  doctest Crawl

  test "greets the world" do
    assert Crawl.hello() == :world
  end
  test "greets with string args" do
    assert Crawl.hello("greeting") == "greeting"
  end
  test "greets with list args" do
    assert Crawl.hello(["a", "b", "c"]) == "a,b,c"
  end
end
