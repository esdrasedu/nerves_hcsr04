defmodule NervesHcsr04 do
  @moduledoc """
  Documentation for NervesHcsr04.
  """

  def distance_from_python do
    drive = :code.priv_dir(:nerves_hcsr04)
    |> to_string()
    |> Path.join("drive.py")
    System.cmd("python", [drive], into: IO.stream(:stdio, :line))
  end

  def distance_from_c_genserve do
    {:ok, sensor} = MyGenServer.start_link({16, 18})
    :ok = MyGenServer.update(sensor)
    Process.sleep(1000)
    {:ok, distance} = MyGenServer.info(sensor)
    distance
  end

end
