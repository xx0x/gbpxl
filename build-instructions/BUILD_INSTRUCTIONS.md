# gbpxl build instructions

The kit contains quite small components, but it's not THAT difficult to solder it. If you haven't soldered SMD stuff before, I would recommend watching some videos how to to that (eg. https://www.youtube.com/watch?v=f9fbqks3BS8).

Also, download the [schematic](https://github.com/xx0x/gbpxl/raw/master/schematic-bom-pcb/gbpxl-schematic.pdf) at first.

*Disclaimer: I'm a self-taught hobbyist, not a "professional" so if you have better tools or practices, use them as you wish.*

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-001.jpg" width="600" />

## The kit contains

| PCB Designator  | Part name                                                  |
|-----------------|------------------------------------------------------------|
| U1              | ATMEGA4809 microcontroller (pre-programmed)                |
| U2              | TPS5430DDAR	buck regulator                                 |
| U3              | MAX232 RS232 transceiver                                   |
| R1              | 10k SMD 0805 resistor                                      |
| R2              | 3.24k SMD 0805 resistor	                                   |
| R3              | 300 SMD 0805 resistor                                      |
| C1              | 100n SMD 0805 capacitor                                    |
| C2,C3           | 4.7u SMD 0805 capacitor                                    |
| C4              | 10n SMD 0805 capacitor                                     |
| C5              | 220u THT capacitor                                         |
| C6,C7,C8,C10,C9 | 470n SMD 0805 capacitors                                   |
| D1              | B340A diode                                                |
| L1              | 22uH power inductor	                                       |
| SW1             | 4 position DIP SWITCH                                      |
| LED1            | 3mm red LED                                                |
| COM1            | DSUB25 male connector                                      |
| -               | Connector case + screws                                    |
| -               | RJ12 power cable (approx 20 cm)                            |
| -               | Game Boy link cable (smaller connector type, approx 55 cm) |
| -               | Cable strain relief                                        |

The kit contains link cable for newer Game Boys (Pocket, Color), since the cables for the original Game Boy are quite hard to get (= expensive). If you want to use it with the original GB, get yourself an adapter as you can see in the video.

## 1. Step: Soldering the components

First, start with the buck regulator. Tin the large pad and one IC pad.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-002.jpg" width="600" />
  
&nbsp;

Then, solder the first IC pin.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-003.jpg" width="600" />

&nbsp;

Turn the PCB upside down, and reheat the large pad using the hole to melt the solder under the chip - while putting a little bit of pressure on the board for the IC to make good contact.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-004.jpg" width="600" />

&nbsp;

Finish soldering the buck regulator, and remember, FLUX is your best friend!

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-005.jpg" width="600" />

&nbsp;
&nbsp;

**NOW PHOTOS ONLY, I'LL ADD THE TEXT DESCRIPTION IN FEW DAYS!**

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-006.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-007.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-008.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-009.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-010.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-011.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-012.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-013.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-014.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-015.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-016.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-017.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-018.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-019.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-020.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-021.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-022.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-023.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-024.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-025.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-026.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-027.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-028.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-029.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-030.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-031.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-032.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-033.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-034.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-035.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-036.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-037.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-038.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-039.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-040.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-041.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-042.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-043.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-044.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-045.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-046.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-047.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-048.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-049.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-050.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-051.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-052.jpg" width="600" />


