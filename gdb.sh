#!/bin/sh

arm-none-eabi-gdb -iex "add-auto-load-safe-path .gdbinit" "$@"
