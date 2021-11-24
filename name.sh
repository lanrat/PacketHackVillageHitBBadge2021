#!/usr/bin/env bash

if [ "$#" -ne 1 ]; then
    echo "Illegal number of parameters, must pass name"
    exit 1
fi

# must be <= 12 chars
name=$1

if [ ${#name} -gt 12 ]; then
  echo "error, name must be <= 12 chars long"
  exit 2
fi

# https://unix.stackexchange.com/questions/267729/how-can-i-print-a-variable-with-padded-center-alignment
center() {
  # replace '\ ' with padding char
  termwidth="14"
  padding="$(printf '%0.1s' \ {1..500})"
  printf '%*.*s %s %*.*s\n' 0 "$(((termwidth-2-${#1})/2))" "$padding" "$1" 0 "$(((termwidth-1-${#1})/2))" "$padding"
}
c_name=$(center $name)

echo "Name: [$c_name]"

sed "s/_BADGE_NAME_/$c_name/g" OLEDi2C.orig.c > OLEDi2C.c

make

make flash

echo "done $name"
