defmodule Pyex do
  def value_receive(value) do
    {:ok, py_exec} = :python.start(python_path: 'lib')
    result = :python.call(py_exec, :py_sample, :value_receive, [value])
    IO.puts("received from python: #{result}")
    :python.stop(py_exec)
  end

  def list_receive(list) when is_list(list) do
    {:ok, py_exec} = :python.start(python_path: 'lib')
    result = :python.call(py_exec, :py_sample, :list_receive, [list])
    IO.puts("received from python: #{result}")
    :python.stop(py_exec)
  end

  def call_class(value) do
    {:ok, py_exec} = :python.start(python_path: 'lib')
    object = :python.call(py_exec, :py_sample, :Sample, [])
    result = :python.call(py_exec, :py_sample, :"Sample.arrange", [object, value])
    IO.puts("received from python: #{result}")
    :python.stop(py_exec)
  end

  def predict() do
    {:ok, py_exec} = :python.start(python_path: 'lib')
    :python.call(py_exec, :predict_sin, :predict, [])
    :python.stop(py_exec)
  end
end
