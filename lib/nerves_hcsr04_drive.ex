defmodule NervesHcsr04Drive do

  @moduledoc ~S"""
  Read HC-SR04 sensor (Sensor of distance, ultra sonic)
  Example usage:
  ```
  iex> defmodule MyGenServer do
         use NervesHcsr04
       end
  :ok
  iex> {:ok, sensor} = MyGenServer.start_link({8, 9})
  :ok
  iex> {:ok, distance} = MyGenServer.info(sensor)
  {:ok, 27.22}
  ```
  You can use `listen` too listen event of sensor too.
  For example:
  ```
  iex> defmodule MyGenServer do
         use NervesHcsr04

         def listen({:ok, e, t, d}) do
           IO.puts("Listen event on MyGenServer")
           IO.puts("Echo: #{e}, Trig: #{t}\n")
           IO.puts("Distance: #{d}\n")
         end
       end
  :ok
  iex> {:ok, sensor} = MyGenServer.start_link({8, 9})
  :ok
  Listen event on MyGenServer
  Echo: 8, Trig: 9
  Distance: 27.20

  Listen event on MyGenServer
  Echo: 8, Trig: 9
  Distance: 27.25
  ```
  """

  defmacro __using__(_opts) do
    quote do

      def start_link({echo, trig}, options \\ []) do
        GenServer.start_link(__MODULE__, {echo, trig}, options)
      end

      def init({echo, trig}) do
        Port.open({:spawn, "#{path()} #{echo} #{trig}"}, [:binary, packet: 2])
        {:ok, {:ok, echo, trig, nil}}
      end

      def handle_info({_port, {:data, data}}, _state) do
        states = :erlang.binary_to_term(data)
        __MODULE__.listen(states)
        {:noreply, states}
      end

      def handle_call(:info, _from, state),
        do: {:reply, state, state}

      defp path, do: "#{:code.priv_dir(:nerves_hcsr04)}/nerves_hcsr04"

      def info(pid) do
        {:ok, _echo, _trig, distance} = GenServer.call(pid, :info)
        {:ok, distance}
      end

      def listen(states), do: states
      defoverridable [listen: 1]

    end
  end

end
