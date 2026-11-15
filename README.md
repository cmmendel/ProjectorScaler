# ProjectorScaler

Portable Windows 10/11 (x64) tool that projects a screen, or a single window, onto a
projector at a chosen size, position and aspect ratio, without touching the projector's
own settings. One EXE, no installer, no .NET.

- **Download:** [`ProjectorScalerPortable.exe`](ProjectorScalerPortable.exe) (or the
  `ProjectorScaler-windows-x64` artifact of the latest *Build and smoke test* run).
- **User guide (Spanish):** [`LEEME.txt`](LEEME.txt).
- **Building:** [`COMPILACION.txt`](COMPILACION.txt) — freestanding C with clang + lld-link,
  no CRT and no Windows SDK; `build-native.sh` builds it on Linux or Git Bash.

The EXE is not code-signed, so SmartScreen may warn on first run.
