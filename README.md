# ProjectorScaler

Portable Windows 10/11 (x64) tool that projects a screen, a single window or a single
Chrome/Edge tab onto a projector at a chosen size, position and aspect ratio, without
touching the projector's own settings. One EXE, no installer, no .NET.

- **Basic mode:** mirrors your screen and lets you size it on the projector with the mouse.
- **Advanced mode:** every option, with the source chosen from stills in three tabs
  (Screens, Windows, Tabs).
- **Spanish / English** switch for the whole app.

Links:

- **Download:** [`ProjectorScalerPortable.exe`](ProjectorScalerPortable.exe) (or the
  `ProjectorScaler-windows-x64` artifact of the latest *Build and smoke test* run).
- **User guide:** [`USER-GUIDE.txt`](USER-GUIDE.txt).
- **Building:** [`BUILDING.txt`](BUILDING.txt) — freestanding C with clang + lld-link,
  no CRT and no Windows SDK; `build-native.sh` builds it on Linux or Git Bash.

The EXE is not code-signed, so SmartScreen may warn on first run.

Developed with Claude Code for [Colegio Mayor Mendel](https://cmmendel.com).
