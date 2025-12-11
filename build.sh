#!/bin/sh

set -e -x

cd /home/justin/roost/

dx bundle --release --platform web "$@" --ssg --out-dir /home/justin/loft/dist/

# cd -
