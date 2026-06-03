#!/bin/bash
set -euo pipefail

: "${RABBITMQ_USER:?set RABBITMQ_USER}"
: "${RABBITMQ_PASSWORD:?set RABBITMQ_PASSWORD}"
: "${RABBITMQ_VHOST:=practice}"

# Create Rabbitmq user
(
  sleep 20

  rabbitmqctl add_user "${RABBITMQ_USER}" "${RABBITMQ_PASSWORD}" 2>/dev/null \
    || rabbitmqctl change_password "${RABBITMQ_USER}" "${RABBITMQ_PASSWORD}"

  rabbitmqctl set_user_tags "${RABBITMQ_USER}" management

  rabbitmqctl set_permissions -p / "${RABBITMQ_USER}" "" "" ""

  if [[ "${RABBITMQ_VHOST}" != "/" ]]; then
    rabbitmqctl add_vhost "${RABBITMQ_VHOST}" 2>/dev/null || true
  fi

  rabbitmqctl set_permissions -p "${RABBITMQ_VHOST}" "${RABBITMQ_USER}" ".*" ".*" ".*"

  echo "*** User '${RABBITMQ_USER}' configured for vhost '${RABBITMQ_VHOST}'. ***"

  echo "*** Log in the WebUI at port 15672. ***"
) &

# $@ is used to pass arguments to the rabbitmq-server command.
# For example if you use it like this: docker run -d rabbitmq arg1 arg2,
# it will be as you run in the container rabbitmq-server arg1 arg2
rabbitmq-server "$@"
