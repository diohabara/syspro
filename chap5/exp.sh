#!/usr/bin/env bash
set -euo pipefail

gcc ./copy2_lowio.c
./a.out original.bin copy.bin

gcc ./copy2_highio.c
./a.out original.bin copy.bin
