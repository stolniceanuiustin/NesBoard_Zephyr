# nes-emulator

NES emulator on the ZedBoard (Zynq-7000) under Zephyr. App is in `app/`, boot
files for flashing are in `bitstreams/nes_emulator/`, flashing tool is the
`tools/zfpga` submodule. Hardware details: `README.md`.

## Workspace layout

This repo is a west manifest repo. zfpga must run from a west workspace:

```
<ws>/.west/
<ws>/zephyr/          fetched by `west update` (fork, branch zynq7000-pl310)
<ws>/nes-emulator/    this repo (clone with --recurse-submodules)
<ws>/.flash.local     per-bench config written by `zfpga init` (not in the repo)
<ws>/build/           zfpga's build dir (created by `zfpga flash`)
```

zfpga finds `<ws>` by walking up from `tools/zfpga` to the nearest dir with
`zephyr/`. Override with `ZFPGA_WS`. It picks up `bitstreams/` of this repo
automatically (override: `ZFPGA_BITSTREAMS`).

Set up once:

```
git clone --recurse-submodules https://github.com/stolniceanuiustin/NesBoard_Zephyr <ws>/nes-emulator
cd <ws> && west init -l nes-emulator && west update
```

If the submodule is empty: `git submodule update --init`.

## Flashing

Needs a ROM and the Zephyr SDK/west environment active. The ROM is not in the
repo.

```
<ws>/nes-emulator/tools/zfpga/zfpga init                 # once per bench
<ws>/nes-emulator/tools/zfpga/zfpga flash nes_emulator -- -DNES_ROM=/abs/path/game.nes
<ws>/nes-emulator/tools/zfpga/zfpga console nes_emulator # UART + boot log
```

- `flash nes_emulator` resolves everything from `bitstreams/nes_emulator/`:
  `.board` (zedboard), `.sample` (`app`), `BOOT.BIN`, `u-boot.img`,
  `system_top.bit`. It builds `app/` with west into `<ws>/build`, then copies
  `BOOT.BIN`, `u-boot.img`, `system.bit` (renamed), `zephyr.bin` and a
  generated `boot.scr` to the SD card's FAT partition.
- Everything after `--` goes to `west build`. `-DNES_ROM` is mandatory, the
  CMake configure fails without it.
- Useful flags: `-p always` (pristine build), `-n` (skip the bitstream, not
  useful here since the VGA/BRAM/GPIO live in the PL).
- `init` asks for the SD target: usbsdmux, a host reader partition, an
  already-mounted dir, or none (then `flash` stages files in
  `<ws>/build/sdcard` and prints manual copy steps) plus the serial device.
- After flashing, power-cycle the ZedBoard. U-Boot loads the bitstream first,
  then Zephyr; the PL must be configured before the app touches BRAM/GPIO.
- Flashing uses `sudo` for mount/usbsdmux and overwrites `BOOT.BIN`,
  `u-boot.img`, `system.bit`, `zephyr.bin`, `boot.scr` on the card (the old
  `boot.scr` is backed up as `boot.scr.linux` once).

## Rules

- Do not run `zfpga flash` or anything that writes to an SD card unless the
  user asks; it modifies physical hardware state.
- Updating the bitstream: replace `bitstreams/nes_emulator/system_top.bit`
  (built from the NesBoard Vivado repo), then rerun `zfpga flash`.
- `tools/zfpga` is a submodule of
  https://github.com/stolniceanuiustin/zephyr-fpga-tools. Changes to zfpga go
  there first; then bump the submodule pointer here. Push the submodule before
  this repo.
- Controller wiring: see the pinout in `README.md` and
  `tests/controller/WIRING.md`. Power it from 3.3 V, never 5 V.
