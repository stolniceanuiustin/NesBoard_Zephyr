# Boot files for nes_emulator (zedboard)

Used by `tools/zfpga` (it picks up `bitstreams/` of this repo automatically).

- `BOOT.BIN`, `u-boot.img`: U-Boot SPL + second stage. U-Boot loads the
  bitstream first, then Zephyr.
- `system_top.bit`: PL design (VGA controller + BRAM + EMIO GPIO), built from
  the NesBoard Vivado project.
- `.board`: `zedboard`. `.sample`: the app dir, `app`.
