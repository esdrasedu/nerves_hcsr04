defmodule NervesHcsr04.MixProject do
  use Mix.Project

  def project do
    [
      app: :nerves_hcsr04,
      version: "0.1.1",
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
      extra_applications: [:logger]
    ]
  end

  defp deps do
    [
      {:elixir_make, "~> 0.4.1"},
      {:ex_doc, ">= 0.0.0", only: :dev}
    ]
  end

  defp description() do
    "Drive of HCSR04 (ultrasonic sensor)"
  end

  defp package() do
    [
      name: "nerves_hcsr04",
      files: ["src/**/*.h", "src/**/*.c", "lib", "priv", "test", "config", "mix.exs", "README.md", "LICENSE", "Makefile"],
      maintainers: ["Esdras Eduardo"],
      licenses: ["GNU 3.0"],
      links: %{"GitHub" => "https://github.com/esdrasedu/nerves_hcsr04"}
    ]
  end
end
