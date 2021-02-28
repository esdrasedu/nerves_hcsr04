# NervesHcsr04
Library to read from the HC_SR04 ultrasonic distance sensor in an Elixir Nerves project.

You always need to set the correct target first, so the C files are cross-compiled with the correct target. 

Add the dependency `{ :nerves_hcsr04, "~> 0.1.3" }` to your mix.exs, then run `mix deps.get && mix deps.compile`.

Afterwards build and upload the firmware to the device. 

More detailed usage instructions are in the file `lib/nerves_hcsr04.ex` as code comments. 
