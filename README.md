# gbpxl

**Game Boy Printer XL**

An *invisible* interface between Game Boy Camera and ESC/POS compatible printers with RS232 serial interface. There was a kit [at Tindie](https://www.tindie.com/products/xx0x/gbpxl-game-boy-printer-xl-kit/) but currently it's sold out. 
Improvements, suggestions, experience with various printer models are welcome!

## Introduction video

[![Video introduction](https://github.com/xx0x/gbpxl/raw/master/docs/gbpxl_video.jpg)](http://www.youtube.com/watch?v=J6ziFhM0pQw "Video introduction")

## How to use it

Build your **gbpxl** using kit (see below).

*or*

**Download the code** from this repository and build it yourself using **Arduino Nano Every** and **TTL-RS232** converter. See the schematic folder for the breadboard design. 

## gbpxl kit

**Kit (SOLD OUT):**

https://www.tindie.com/products/xx0x/gbpxl-game-boy-printer-xl-kit/

**Build instructions:**

https://github.com/xx0x/gbpxl/blob/master/build-instructions/BUILD_INSTRUCTIONS.md

**Gerber file and BOM are available here, if you want to make your own PCBs:**

https://github.com/xx0x/gbpxl/tree/master/schematic-bom-pcb

**How it looks:**

<img src="https://github.com/xx0x/gbpxl/raw/master/docs/gbpxl_1.jpg" width="260" /> <img src="https://github.com/xx0x/gbpxl/raw/master/docs/gbpxl_2.jpg" width="260" />

## Tested with these printers
Originally intended only for Epson TM-T88 family, but it should work with *most* ESC/POS printers by selecting different DIP settings.

| Printer             | DIP3  | DIP4  |                            
|:--------------------|:-----:|:-----:|
|Epson TM-T88III      |   OFF | ON    |
|Epson TM-T88IV       |   ON  | ON    |
|Wincor Nixdorf TH230 |   ON  | OFF   |
|HPRT PPTII-A         |   OFF | OFF   |


## gbpxl DIP switch settings

|     | DIP1: Scale | DIP2: Cut | DIP3: Baud rate | DIP4: Method   |
|-----|:-----------:|-----------|-----------------|----------------|
| ON  |   3x        | Yes       | 38400           | GS             |
| OFF |   2x        | No        | 9600            | ESC \*         |

### Scale
 * 2x scale is intended for 58 mm thermal printers
 * 3x scale is intended for 80 mm thermal printers

### Cut
Cuts the paper after printing each photo. (Some cheaper printers don't support it.)

### Baud rate
Must be the same as selected by the printer (see the manual). If you are not sure, try 9600.
 * Epson TM-T88 family: DIP switches under metal cover on the bottom.
 * Wincor Nixdorf TH230: Selected in the menu (the menu is activated by holding Feed button while powering the printer on).

### GS method
 * "Gs v 0" if baudrate 9600
 * "Gs ( L" if baudrate 38400


## How to wire the board

The link cable contains VCC as well, so in theory it could be used to power gbpxl. But in reality, the provided voltage/current is not enough to run gbpxl without issues, mostly since the MAX232 chip boosts TTL logic levels to higher voltages used by RS232 interface. That's why I decided to include buck regulator and power the device from printer's accessory port. If you want to power gbpxl directly with 5V, use VCC pad located in UPDI.

### Game Boy Link Connector
Cable at the end which plugs into the Game Boy.

```
  ___________
 |  6  4  2  |                
  \_5__3__1_/     
                            
2. SO (serial output)       |  BROWN / GREEN*
3. SI (serial input)        |  GREEN / BROWN*
5. SC (serial clock)        |  BLUE*
6. GND                      |  RED*
```

\*Color codes for cheap Game Boy Color link cable, which you can buy on eBay etc.
GREEN/BROWN color are swapped in each cable - you must try both variants or use your multimeter.
  
### RJ-12 connector (power from printer's "DK" port)
Cable at the end which plugs into the printer.

```
  ____===____
 |           |
 |___________|
  | | | | | |
  1 2 3 4 5 6 

4. VIN (24 V)
6. GND 
```
Gbpxl board supports 10-30 V as VIN voltage.
 
### ...if using Arduino Every
  
  * SO = Arduino pin 4
  * SI = Arduino pin 3
  * SC = Arduino pin 2
  
 Don't connect RJ-12 to Arduino Nano Every, it's VIN input supports 21 V max!
 
 ## Programming gbpxl
 
Since gbpxl uses ATmega4809, the programming must be done via **UPDI** interface, you can't use just your regular USBasp or similar. The UPDI connector uses the pinout based on **[microUPDI project](https://github.com/MCUdude/microUPDI)**, which also includes TX/RX connections for easy communication with PC - useful for transfering images etc.

Sadly, since the UPDI is quite new, there are no cheap programmers available yet, but you can build the **[microUPDI](https://github.com/MCUdude/microUPDI)** or **[jtag2updi](https://github.com/ElTangas/jtag2updi)** quite easily by yourself. When uploading, specify "Arduino Nano Every" as your pinout.

<img src="https://github.com/xx0x/gbpxl/raw/master/docs/gbpxl_updi.jpg" width="500" />

**Don't forget to unplug the power before connecting UPDI, since the programmer usually powers the device!**

 ## Additional stuff
 
 ### BTN
As you can see in the photos and in the schematic, gbpxl also includes a *hidden button*. It's not populated by default, since there was no space for a microswitch, but you can use tweezers or a wired button for more permanent solution. Its' function is to print the last photo (stored in the buffer) again. It's a useful feature for selecting various settings with DIP switches and for development - since you don't have to wait for the transfer between Game Boy and gbpxl.

If you trigger the button when nothing has been printed yet, it will print the photo of the gbpxl author (stored in test_image_custom_frame.h) :-)

 ### LED
 The LED may look kind of useless, since it's hidden inside the case, but it's useful for development and problem solving with data transfer, since it blinks when recieving or sending data. If you want, you can always drill a hole in the plastic connector case to see the LED blinking...
 
 ## Author
 
**Václav Mach**
* http://www.xx0x.cz
* http://www.vaclav-mach.cz
 
 ## Thanks!
 
 Big thanks to Brian Khuu for decoding the GBP protocol
 and making Arduino Game Boy Printer Emulator
 https://github.com/mofosyne/arduino-gameboy-printer-emulator 
