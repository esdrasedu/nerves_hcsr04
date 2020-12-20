defmodule NervesHcsr04 do


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
  iex> :ok = MyGenServer.update(sensor)
  :ok
  iex> Process.sleep(1000)
  :ok
  iex> {:ok, distance} = MyGenServer.info(sensor)
  {:ok, 27.22}
  ```
  You can use `listen` to listen event of sensor too.
  For example:
  ```
  iex> defmodule MyGenServer do
         use NervesHcsr04
         def listen({:ok, d, _port, {e, t}}) do
           Logger.info("Success on MyGenServer")
           Logger.info("Echo: #{e}, Trig: #{t}\n")
           Logger.info("Distance: #{d}\n")
         end
         def listen({:error, code_error, _port, {e, t}}) do
           Logger.info("Error on MyGenServer")
           Logger.info("Echo: #{e}, Trig: #{t}\n")
           Logger.info("Error: #{code_error}\n")
         end
       end
  :ok
  iex> {:ok, sensor} = MyGenServer.start_link({8, 9})
  :ok
  iex> :ok = MyGenServer.update(sensor)
  :ok
  Success on MyGenServer
  Echo: 8, Trig: 9
  Distance: 27.20
  iex> {:ok, sensor} = MyGenServer.start_link({8, 10})
  :ok
  iex> :ok = MyGenServer.update(sensor)
  :ok
  Error on MyGenServer
  Echo: 8, Trig: 9
  Error: -2
  ```

  The error codes are:
    SUCCESS 0
    ERROR_INIT_GPIO -1
    TIMEOUT_PING -2
    TIMEOUT_PONG -3
    ERROR_GPIO_PIN -4
  """

  defmacro __using__(_opts) do
    quote do

      def start_link({echo, trig}, options \\ []) do
        GenServer.start_link(__MODULE__, {echo, trig}, options)
      end

      def init({echo, trig}) do
        port = Port.open({:spawn, "#{path()} #{echo} #{trig}"}, [:binary, packet: 2])
        {:ok, {:ok, nil, port, {echo, trig}}}
      end

      def handle_info({port, {:data, data}}, _state) do
        {type, echo, trig, result} = List.first(:erlang.binary_to_term(data))

        states = {type, result, port, {echo, trig}}
        __MODULE__.listen(states)
        {:noreply, states}
      end

      def handle_cast(:update, {_type, _result, port, _pins} = state) do
        true = Port.command(port, "update")
        {:noreply, state}
      end

      def handle_call(:info, _from, state),
        do: {:reply, state, state}

      defp path, do: "#{:code.priv_dir(:nerves_hcsr04)}/nerves_hcsr04"

      def update(pid) do
        GenServer.cast(pid, :update)
      end

      def info(pid) do
        {type, result, _port, _pins} = GenServer.call(pid, :info)
        {type, result}
      end

      def listen(states), do: states
      defoverridable [listen: 1]

    end
  end

end
