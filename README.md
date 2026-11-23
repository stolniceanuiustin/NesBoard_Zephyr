# nes-emulator

NES emulator for the Avnet ZedBoard (Zynq-7000), running on Zephyr. Frames are
written to a BRAM framebuffer scanned out by the VGA controller in the PL
(Vivado project: https://github.com/stolniceanuiustin/NesBoard).

```
app/              emulator (src/{cpu,ppu,bus,input,video}, include/, boards/zedboard.overlay)
tests/controller/ standalone NES controller GPIO test (see WIRING.md)
tools/pc_viewer/  optional UDP framebuffer viewer
west.yml          Zephyr (upstream + PL310 L2 cache) pinned via west
```

## Build

```
git clone https://github.com/stolniceanuiustin/NesBoard_Zephyr ws/nes-emulator
cd ws && west init -l nes-emulator && west update
west build -b zedboard nes-emulator/app -- -DNES_ROM=/path/to/game.nes
```

The ROM is not in the repo. Load the bitstream from the NesBoard repo.

## NES controller pinout

Standard NES controller plug, numbered as in the NES pinout (pin 1 is the
square pad / closest to the flat edge of the plug):

| NES pin | Signal | ZedBoard JA PMOD | EMIO / Zephyr |
|---------|--------|------------------|---------------|
| 1 | GND | GND | - |
| 2 | CLOCK | JA2 (AA11) | `psgpio_bank2` pin 1 |
| 3 | LATCH | JA1 (Y11) | `psgpio_bank2` pin 0 |
| 4 | DATA | JA3 (Y10) | `psgpio_bank2` pin 2 |
| 5 | N/C | - | - |
| 6 | N/C | - | - |
| 7 | VCC | JA VCC (3.3 V) | - |

Power the controller from the PMOD's 3.3 V so DATA stays within the Zynq
LVCMOS33 input range. Pin assignments live in `app/boards/zedboard.overlay` and the Vivado
XDC.

## Flashing

`tools/zfpga` is a submodule (zephyr-fpga-tools). Clone with
`--recurse-submodules`, or run `git submodule update --init` afterwards.
See `tools/zfpga/README.md` for the zedboard flashing workflow.
