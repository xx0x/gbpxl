# gbpxl

**Game Boy Printer XL**

Interface between Game Boy Camera and ESC/POS compatible printers 
made by Vaclav Mach (www.xx0x.cz/gbpxl)

## How to build it

using custom gbpxl board

*or*

Arduino Nano Every + TTL->RS232 converter

## Tested with these printers

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

### GS method
 * "Gs v 0" when baudrate 9600
 * "Gs ( L" when baudrate 38400

## How to wire the board

### Game Boy Link Connector
Cable at the end which plugs into the Game Boy.

```
  ___________
 |  6  4  2  |                
  \_5__3__1_/     
                            
2. SO (serial output)       |  BROWN*
3. SI (serial input)        |  GREEN*
4. SC (serial clock)        |  BLUE*
6. GND                      |  RED*
```

\*Color codes for cheap Game Boy Color link cable, which you can buy on eBay etc.
  
### RJ-12 connector (power from printer's "DK" port)
Cable at the end which plugs into the printer.

```
  ___________
 |           |
 |___________|
  | | | | | |
  1 2 3 4 5 6 

1. GND 
3. VIN (24 V)
```
Gbpxl board supports 10-30 V as VIN voltage.
 
### ...if using Arduino Every
  
  * SO = Arduino pin 4
  * SI = Arduino pin 3
  * SC = Arduino pin 2
  
 Don't connect RJ-12 to Arduino Nano Every, it's VIN input supports 21 V max!
 
 ## Thanks!
 
 Big thanks to Brian Khuu for decoding the GBP protocol
 and making Arduino Game Boy Printer Emulator
 https://github.com/mofosyne/arduino-gameboy-printer-emulator 
