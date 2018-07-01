defmodule Pyex do
  def value_receive( value ) do
    { :ok, py_exec } = :python.start( [ python_path: 'lib' ] )
    result = :python.call( py_exec, :py_sample, :value_receive, [ value ] )
    IO.puts "received from python: #{result}"
    :python.stop( py_exec )
  end
end
