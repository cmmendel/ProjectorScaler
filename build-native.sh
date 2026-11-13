#!/usr/bin/env bash
set -euo pipefail
cd "$(dirname "$0")"
mkdir -p build
cd build
for dll in kernel32 user32 gdi32; do
  lld-link /machine:x64 /dll /noentry /def:"$dll.def" /out:"$dll.dll" /implib:"$dll.lib"
done
clang --target=x86_64-pc-windows-msvc -O2 -c -ffreestanding -fno-builtin -Wall -Wextra ../ProjectorScalerPortable.c -o ProjectorScalerPortable.obj
lld-link /machine:x64 /subsystem:windows /nodefaultlib /entry:mainCRTStartup /out:../ProjectorScalerPortable.exe ProjectorScalerPortable.obj kernel32.lib user32.lib gdi32.lib
