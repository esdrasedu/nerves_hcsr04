defmodule MyGenServer do
  use NervesHcsr04Drive

  def listen({:ok, e, t, d}) do
    IO.puts("Listen event on MyGenServer")
    IO.puts("Echo: #{e}, Trig: #{t}\n")
    IO.puts("Distance: #{d}\n")
  end

  def listen({:error, error}) do
    IO.puts("Error: #{error}\n")
  end

end
