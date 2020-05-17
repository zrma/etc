#!/bin/bash

set -euf

echo "Hello ${INPUT_who}!"

echo '{"script_output": "We had a great time running this script. Thanks."}' > $1
