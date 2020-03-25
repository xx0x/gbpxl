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
| C6,C7,C8,C9,C10 | 470n SMD 0805 capacitors                                   |
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

Tin one or two pads for the ATmega. Then, while reheating the pad, push the MCU into it with your tweezers.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-006.jpg" width="600" />

&nbsp;

Solder the oposite legs.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-007.jpg" width="600" />

&nbsp;

Then, make sure everything's how it's supposed to be and solder the rest. If you end up with solder bridges, you can use solder wick for sucking the excess solder.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-008.jpg" width="600" />

&nbsp;

You should end up with something like this.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-009.jpg" width="600" />

&nbsp;

Next, solder the 0805 capacitors and resistors. Resistors are easier, since they have their value written on them. I've manually marked 10nF and 100nF capacitors since they look almost identical and there is one piece of each.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-010.jpg" width="600" />

&nbsp;

You can use exacto knife for separating the protective layer.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-011.jpg" width="600" />

&nbsp;

Again, tin one pad and then drag the component into the solder while reheating it. The polarity isn't important when soldering this capacitor.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-012.jpg" width="600" />

&nbsp;

Then, solder the opposite side.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-013.jpg" width="600" />

&nbsp;

I usually pre-tin pads for all components at once.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-014.jpg" width="600" />

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-015.jpg" width="600" />

&nbsp;

The result should look like this.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-016.jpg" width="600" />

&nbsp;

Now let's continue with the bottom side. Watch out - the diode is polarized (the strip on the diode must match the strip on the PCB).

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-017.jpg" width="600" />

&nbsp;

Then, prepare the pads for the inductor. I usually tin both pads, one with more solder.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-018.jpg" width="600" />

&nbsp;

Then drag the inductor into the solder while reheating the pad with more solder.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-019.jpg" width="600" />

&nbsp;

Then finish it by reheating the other pad from the side - adding little bit of solder helps!

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-020.jpg" width="600" />

&nbsp;

Next comes the big capacitor - which has to be mounted sideways because of the clearance. The longer leg is the positive contact.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-021.jpg" width="600" />

&nbsp;

Bend the capacitor inside the PCB hole and solder it.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-022.jpg" width="600" />

&nbsp;

Then, cut the legs.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-023.jpg" width="600" />

&nbsp;

Solder the 3mm diode, the short leg goes to the flat side (closer to the RS232 connector).

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-024.jpg" width="600" />

&nbsp;

Now, *almost complete*! :-)

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-025.jpg" width="600" />

## 2. Step: Adjusting the case

Cut the unnecessary plastic supports, use flush cutters or a dremel tool. It doesn't have to look perfect, since it will be hidden inside. Just don't break the outside of the case.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-026.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-027.jpg" width="600" />

## 3. Step: Soldering the RS232 connector

Position the connector and PCB into the case. Support the PCB with something (eg. your tweezers) on the side opposite the connector and try to align everything as best as possible.

**Solder only two contacts!**

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-028.jpg" width="600" />

&nbsp;

Then, take out the PCB and solder one contact on the opposite side.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-029.jpg" width="600" />

&nbsp;

Make sure everything's straight and that it fits inside the connector case. Since **the last thing you want to do is having to de-solder the connector** because it doesn't fit inside.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-030.jpg" width="600" />

&nbsp;

If everything fits, solder the rest of pins on both sides. Use a lot of solder to make the connection strong!

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-031.jpg" width="600" />

## 4. Step: Cleaning

Next, use some rubbing alcohol for cleaning the flux remainings. I like to clean the PCB now, since it's much easier without the DIP switch.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-032.jpg" width="600" />

&nbsp;

**Much better!**

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-033.jpg" width="600" />

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-034.jpg" width="600" />

## 5. Step: DIP Switch soldering

Solder the two opposite pins while holding the DIP switch inside. 

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-035.jpg" width="600" />

&nbsp;

If everything's OK and flat, solder the remaining pins.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-036.jpg" width="600" />

&nbsp;

**Almost there!**

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-037.jpg" width="600" />

## 6. Step: Cable relief adjustments

The cable relief is kind of long by default - it's not neccessary, but it's better to shorten it to approx 2.5cm.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-038.jpg" width="600" />

&nbsp;

Next, cut 2 small notches for the PCB (approx 2mm wide).

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-039.jpg" width="600" />
<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-040.jpg" width="600" />

&nbsp;

Everything should fit nicely.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-041.jpg" width="600" />

## 7. Step: Cables

First, prepare the link cable. Strip it and cut the unnecessary cables. You will only need BROWN/GREEN (SO), GREEN/BROWN (SI), BLUE (SC), RED (GND) cables. Pre-tin them.


SO/SI are serial output/input lines and inside each cable they are swapped. Since the cable you get with the gbpxl kit was originally split in half, you must use your multimeter or try both variants, if the transfer doesn't work. The colors may differ, check the pinout for the reference.

```
  ___________
 |  6  4  2  |                
  \_5__3__1_/     
                            
2. SO (serial output)       |  BROWN / GREEN
3. SI (serial input)        |  GREEN / BROWN
5. SC (serial clock)        |  BLUE
6. GND                      |  RED
```

**Don't forget to pull the cable through the cable relief!**

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-042.jpg" width="600" />

&nbsp;

Solder the connections.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-043.jpg" width="600" />

&nbsp;

Next, solder the power cable in the similar way. RED (VIN), GREEN (GND).

**Don't forget to pull the cable through the cable relief before soldering!**

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-044.jpg" width="600" />

## 8. Step: First test

Plug the gbpxl into the printer, connect the power cable and power the printer on. The red LED should light on within fraction of second - that means the device is ready. **If the LED doesn't turn on, immediately unplug the device and check all the solder connections for possible solder bridges etc.**

If everything's fine, set the DIP switches according to your printer (baud rate, method).

I know that my printer is set to 38400 baud rate, that's why the 3rd switch is ON. If you are not sure, try to turn all switches off.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-045.jpg" width="600" />

&nbsp;

Then, when device is running, short the two pads called BTN. That should print a test image stored in the buffer when the device turns on.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-046.jpg" width="600" />

&nbsp;

The printer should start printing and the result should look like this. (That's me, lol).

This was printed with 2x scaling and ESC * method. But since my printer is 80 mm type and supports *modern* printing method with less banding, I changed the settings to 3x scaling and GS ( L method by turning switches 1 and 4 to ON position. You will find all the combinations in the README here on GitHub.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-047.jpg" width="600" />

&nbsp;

Next, connect your Game Boy and try to print a photo from it.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-048.jpg" width="600" />

## 9. Step: Finishing touches

Use hot glue to secure the cables inside the cable relief.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-049.jpg" width="600" />

&nbsp;

I used red hot glue, but any hot glue should work the same...

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-050.jpg" width="600" />

&nbsp;

Screw everything together.

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-051.jpg" width="600" />

## 10. Step: Enjoy!

Don't forget to share your results on your favorite social network using #gbpxl tag!

<img src="https://github.com/xx0x/gbpxl/raw/master/build-instructions/img/gbpxl-build-052.jpg" width="600" />


