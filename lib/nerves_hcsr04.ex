defmodule NervesHcsr04 do
  @moduledoc """
  Documentation for NervesHcsr04.
  """

  def distance_from_python do
    drive = :code.priv_dir(:nerves_hcsr04)
    |> to_string
    |> Path.join("drive.py")
    System.cmd "python", [drive], into: IO.stream(:stdio, :line)
  end
end
