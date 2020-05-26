#!/bin/bash

set -euf

echo "deploy with ${INPUT_host} ${INPUT_username} ${INPUT_password}"

echo '{"database_url": "${INPUT_username}:${INPUT_password}@${INPUT_host}"}' > $1
