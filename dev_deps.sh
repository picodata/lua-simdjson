#!/bin/sh
# Call this script to install dependencies for development purposes.

set -e

# Test dependencies:
tarantoolctl rocks install luacheck 0.26.0
tarantoolctl rocks install luatest 0.5.6
