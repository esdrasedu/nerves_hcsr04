defmodule NervesHcsr04 do
  @moduledoc """
  Documentation for NervesHcsr04.
  """

  def distance_from_python do
    drive = :code.priv_dir(:nerves_hcsr04)
    |> to_string()
    |> Path.join("drive.py")
    System.cmd "python", [drive], into: IO.stream(:stdio, :line)
  end

  def distance_from_c_line do
    :code.priv_dir(:nerves_hcsr04)
    |> to_string()
    |> Path.join("nerves_hcsr04")
    |> System.cmd(["16", "18"], into: IO.stream(:stdio, :line))
  end

  def distance_from_c_genserve do
    {:ok, sensor} = MyGenServer.start_link({16, 18})
    {:ok, distance} = MyGenServer.info(sensor)
    distance
  end

end
