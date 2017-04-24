defmodule Cache do
  @moduledoc false
  
  use GenServer

  def start_link do
    :gen_server.start_link({:local, :cache}, __MODULE__, {%{}, 0}, [])
  end

  def put(url, page) do
    :gen_server.cast(:cache, {:put, url, page})
  end

  def get(url) do
    :gen_server.call(:cache, {:get, url})
  end

  def size do
    :gen_server.call(:cache, {:size})
  end

  def handle_cast({:put, url, page}, {pages, size}) do
    new_pages = Map.put(pages, url, page)
    new_size = size + byte_size(page)
    {:noreply, {new_pages, new_size}}
  end

  def handle_call({:get, url}, _from, {pages, size}) do
      {:reply, pages[url], {pages, size}}
  end

  def handle_call({:size}, _from, {pages, size}) do
      {:reply, size, {pages, size}}
  end
end


defmodule CacheSupervisor do
  @moduledoc false

  use Supervisor

  def start_link do
    :supervisor.start_link(__MODULE__, [])
  end

  def init(_arg) do
    workers = [
      worker(Cache, [])
    ]

    supervise(workers, strategy: :one_for_one)
  end
end