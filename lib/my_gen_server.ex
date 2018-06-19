defmodule MyGenServer do
  use NervesHcsr04Drive

  def listen({:ok, d, _port, {e, t}}) do
    IO.puts("Success on MyGenServer")
    IO.puts("Echo: #{e}, Trig: #{t}\n")
    IO.puts("Distance: #{d}\n")
  end

  def listen({:error, code_error, _port, {e, t}}) do
    IO.puts("Error on MyGenServer")
    IO.puts("Echo: #{e}, Trig: #{t}\n")
    IO.puts("Error: #{code_error}\n")
  end

end
