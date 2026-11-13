#!/usr/bin/env bash
# Builds ProjectorScalerPortable.exe with clang + lld, no CRT and no Windows SDK.
# Linux: needs clang, lld-link and llvm-rc on PATH.
# Windows (Git Bash): point the three variables at zig's copies, see COMPILACION.txt.
set -euo pipefail
export MSYS2_ARG_CONV_EXCL="*"   # Git Bash would otherwise turn /dll into a path
CLANG="${CLANG:-clang}"
LLD_LINK="${LLD_LINK:-lld-link}"
RC="${RC:-llvm-rc}"
cd "$(dirname "$0")"
mkdir -p build
cd build
for dll in kernel32 user32 gdi32; do
  $LLD_LINK /machine:x64 /dll /noentry /def:"$dll.def" /out:"$dll.dll" /implib:"$dll.lib"
done
$RC /fo ProjectorScaler.res ../ProjectorScaler.rc
$CLANG --target=x86_64-pc-windows-msvc -O2 -c -ffreestanding -fno-builtin -Wall -Wextra ../ProjectorScalerPortable.c -o ProjectorScalerPortable.obj
$LLD_LINK /machine:x64 /subsystem:windows /nodefaultlib /entry:mainCRTStartup /out:../ProjectorScalerPortable.exe ProjectorScalerPortable.obj ProjectorScaler.res kernel32.lib user32.lib gdi32.lib
