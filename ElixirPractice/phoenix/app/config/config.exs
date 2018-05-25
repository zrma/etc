# This file is responsible for configuring your application
# and its dependencies with the aid of the Mix.Config module.
#
# This configuration file is loaded before any dependency and
# is restricted to this project.
use Mix.Config

# General application configuration
config :phoenix_docker,
  ecto_repos: [PhoenixDocker.Repo]

# Configures the endpoint
config :phoenix_docker, PhoenixDocker.Endpoint,
  url: [host: "localhost"],
  secret_key_base: "2nRZEao3KIIZ9IkkRBh0+kD/lJA8JDPD3shYv0Ghd/OLuMSwt7f/ViNKADvtuvYK",
  render_errors: [view: PhoenixDocker.ErrorView, accepts: ~w(html json)],
  pubsub: [name: PhoenixDocker.PubSub,
           adapter: Phoenix.PubSub.PG2]

# Configures Elixir's Logger
config :logger, :console,
  format: "$time $metadata[$level] $message\n",
  metadata: [:request_id]

# Import environment specific config. This must remain at the bottom
# of this file so it overrides the configuration defined above.
import_config "#{Mix.env}.exs"
