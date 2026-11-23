# nes-app

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
git clone https://github.com/stolniceanuiustin/nes-app nes-ws/nes-app
cd nes-ws && west init -l nes-app && west update
west build -b zedboard nes-app/app -- -DNES_ROM=/path/to/game.nes
```

The ROM is not in the repo. Load the bitstream from the NesBoard repo.
