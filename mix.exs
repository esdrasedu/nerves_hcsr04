defmodule NervesHcsr04.MixProject do
  use Mix.Project

  def project do
    [
      app: :nerves_hcsr04,
      version: "0.1.0",
      compilers: [:elixir_make] ++ Mix.compilers(),
      description: description(),
      package: package(),
      build_embedded: Mix.env == :prod,
      start_permanent: Mix.env() == :prod,
      deps: deps()
    ]
  end

  def application do
    [
      mod: {NervesHcsr04.Application, []},
      extra_applications: [:logger]
    ]
  end

  defp deps do
    [{:elixir_make, "~> 0.4.1"}]
  end

  defp description() do
    "Drive of HCSR04 (ultrasonic sensor)"
  end

  defp package() do
    [
      name: "nerves_hcsr04",
      files: ["lib", "priv", "mix.exs", "README.md"],
      maintainers: ["Esdras Eduardo"],
      licenses: ["Apache 2.0"],
      links: %{"GitHub" => "https://github.com/esdrasedu/nerves_hcsr04"}
    ]
  end
end
