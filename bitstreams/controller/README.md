# Boot files for 'controller' (zedboard)

Put everything this sample needs to boot in THIS folder:

- `system_top.bit`  (your PL design; `system_top.xsa` works too, zfpga extracts the .bit)
- `BOOT.BIN`  (your U-Boot build -- see zfpga/docs/boot-chain.md)
- `u-boot.img`  (SPL second stage)

zfpga looks here first for BOOT.BIN/u-boot.img. If you'd rather share one
boot chain across samples, omit it here and set BOOTBIN_zedboard/UBOOT_IMG_zedboard
in .flash.local instead.

The Zephyr app is yours: zfpga builds nes-emulator/tests/controller.
Then: `zfpga flash controller`
