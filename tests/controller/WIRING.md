# NES Controller Wiring - ZedBoard JA PMOD

See `doc/NES_Controller_pinout.jpg` in the repo root for the connector photo.

## Controller plug (standard NES pinout)

| NES pin | Signal |
|---------|--------|
| 1       | GND    |
| 2       | CLOCK  |
| 3       | LATCH  |
| 4       | DATA (serial out from controller) |
| 5       | N/C    |
| 6       | N/C    |
| 7       | VCC    |

## ZedBoard JA PMOD header (top row, left to right)

```
JA1  JA2  JA3  JA4  GND  VCC(3.3V)
```

## Connection table

| NES pin | Signal | Wire to      |
|---------|--------|--------------|
| 1       | GND    | JA GND       |
| 2       | CLOCK  | JA2          |
| 3       | LATCH  | JA1          |
| 4       | DATA   | JA3          |
| 7       | VCC    | JA VCC (3.3 V) |

Power the controller from the PMOD's 3.3 V, not 5 V: DATA goes straight into
a 3.3 V Zynq input.

## Vivado XDC constraints

```tcl
set_property PACKAGE_PIN Y11  [get_ports {GPIO_0_0_tri_io[0]}]  ;# JA1 = LATCH
set_property PACKAGE_PIN AA11 [get_ports {GPIO_0_0_tri_io[1]}]  ;# JA2 = CLOCK
set_property PACKAGE_PIN Y10  [get_ports {GPIO_0_0_tri_io[2]}]  ;# JA3 = DATA
set_property IOSTANDARD LVCMOS33 [get_ports {GPIO_0_0_tri_io[*]}]
```

## Zephyr devicetree (boards/zedboard.overlay)

EMIO GPIO starts at `psgpio_bank2`, pin 0.

```
EMIO[0] = JA1 = LATCH -> psgpio_bank2 pin 0
EMIO[1] = JA2 = CLOCK -> psgpio_bank2 pin 1
EMIO[2] = JA3 = DATA  -> psgpio_bank2 pin 2
```
