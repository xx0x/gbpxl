/**
 * gbpxl (Game Boy Printer XL)
 * 
 * Interface between Game Boy Camera and ESC/POS compatible printers
 * 
 * Made by Vaclav Mach (www.xx0x.cz/gbpxl)
 * 
 * USE WITH:
 * 
 * a) custom gbpxl board (github.com/xx0x/gbpxl)
 * b) Arduino Nano Every + TTL->RS232 converter
 * 
 * DIP SWITCH SETTINGS:
 *
 * 1: SCALE
 * OFF: 2x
 * ON: 3x
 * 
 * 2: CUT after each print
 * OFF: No
 * ON: Yes
 * 
 * 3: BAUD RATE
 * OFF: 9600
 * ON: 38400
 * 
 * 4: METHOD
 * OFF: "ESC *"
 * ON: "Gs v 0" when baudrate 9600
 *     "Gs ( L" when baudrate 38400
 * 
 * TESTED WITH:             DIP  3  |  4
 * Epson TM-T88III:             OFF | ON
 * Epson TM-T88IV:              ON  | ON
 * Wincor Nixdorf TH230:        ON  | OFF
 * HPRT PPTII-A:                OFF | OFF
 * 
 * HOW TO WIRE THE BOARD:
 * 
 * Game Boy Link Connector
 * (cable at the end which plugs into the Game Boy)
 *  ___________
 * |  6  4  2  |                
 *  \_5__3__1_/                 |  color codes
 *                              |  (cheap cable from eBay)
 * 2 = SO (serial output)       |  BROWN
 * 3 = SI (serial input)        |  GREEN
 * 4 = SC (serial clock)        |  BLUE
 * 6 = GND                      |  RED
 * 
 * RJ-12 connector (power from printer's "DK" port)
 * (cable at the end which plugs into the printer) 
 *  ___________
 * |           |
 * |___________|
 *  | | | | | |
 *  1 2 3 4 5 6 
 *
 * 1 = GND 
 * 3 = VIN (24 V)
 * The gbpxl board supports 10 - 30 V as VIN voltage.
 * 
 * 
 * IF USING NANO EVERY:
 * 
 * SO = Arduino pin 4
 * SI = Arduino pin 3
 * SC = Arduino pin 2
 * 
 * Don't connect RJ-12 to Arduino Nano Every, it supports 21 V max!
 * 
 * Big thanks to Brian Khuu for decoding the GBP protocol
 * and making Arduino Game Boy Printer Emulator
 * https://github.com/mofosyne/arduino-gameboy-printer-emulator
 * 
 */

#include "gbp/gameboy_printer.cpp"
#include "test_image_custom_frame.h"

// PINS (Arduino Nano Every)
#define PIN_DIP_SCALE 8
#define PIN_DIP_CUT 7
#define PIN_DIP_BAUDRATE 6
#define PIN_DIP_METHOD 5
#define PIN_BTN 9
#define PIN_LED 13

// IMAGE DEFINITION
#define TILE_PIXEL_WIDTH 8
#define TILE_PIXEL_HEIGHT 8
#define TILES_PER_LINE 20
#define IMG_WIDTH 160
#define IMG_HEIGHT 144
#define EPSON_BYTES_PER_LINE 20

// BUFFER OPTIONS
#define BUFFER_SIZE 2880
byte printBuffer[BUFFER_SIZE]; // buffer stores data as raster bitmap, in rows
unsigned int totalBytes = 0;   // bytes recieved from GameBoy
#define LINES_AT_ONCE_XL 48    // if your printer wont print the whole image, try values: 36, 24, 16

// SETTINGS
#define SLOW_BAUD_RATE 9600
#define FAST_BAUD_RATE 38400
#define PARTIAL_CUT 66
#define FULL_CUT 65
#define PC_BAUD_RATE 115200
#define ESC_PRINT_METHOD 0
#define GS_PRINT_METHOD 1

byte scale = 2;                          // DIP switch 1
byte cut = false;                        // DIP switch 2
unsigned long baudRate = SLOW_BAUD_RATE; // DIP switch 3
byte method = ESC_PRINT_METHOD;          // DIP switch 4
byte cutMode = FULL_CUT;                 // full cut is not supported by TM88, but works with other

// DEBUG STUFF
#define COPY_TEST_IMAGE_TO_BUFFER 1
#define SEND_TO_PC_AFTER_PRINTING 0
#define STARTUP_PRINTER_TEST 1

/**
 * Initial setup
 */
void setup()
{
    Serial.begin(PC_BAUD_RATE);

    pinMode(PIN_DIP_SCALE, INPUT_PULLUP);
    pinMode(PIN_DIP_METHOD, INPUT_PULLUP);
    pinMode(PIN_DIP_CUT, INPUT_PULLUP);
    pinMode(PIN_DIP_BAUDRATE, INPUT_PULLUP);
    pinMode(PIN_BTN, INPUT_PULLUP);
    pinMode(PIN_LED, OUTPUT);
    digitalWrite(PIN_LED, LOW);

    gameboy_printer_setup();
    delay(100);

    updateDipSwitches();
    delay(100);

    epson_start();
    delay(100);
    epson_feed(2);

#if COPY_TEST_IMAGE_TO_BUFFER
    copyTestImageToBuffer();
#endif

#if STARTUP_PRINTER_TEST
    Serial.println("Sending test print");
    printerTest();
#endif

    Serial.println("Device loaded, waiting for print data...");
    digitalWrite(PIN_LED, HIGH);
}

/**
 * Loops and waits for the data and commands
 */
void loop()
{
    updateDipSwitches();
    bool schedulePrint = false;

    // Packet received from gameboy
    if (gbp_printer.packet_ready_flag)
    {
        digitalWrite(PIN_LED, LOW);

        // Indicate To The Byte Scanner and the Message Parser to scan for new packet
        gbp_rx_tx_byte_reset(&(gbp_printer.gbp_rx_tx_byte_buffer));
        gbp_parse_message_reset(&(gbp_printer.gbp_packet_parser));

        // Process this packet
        switch (gbp_printer.gbp_packet.command)
        {
        case GBP_COMMAND_INIT:
        { // This clears the printer status register (and buffers etc... in the real printer)
            gbp_printer.gbp_printer_status = {0};
            clearBuffer();
            break;
        }
        case GBP_COMMAND_DATA:
        { // This is called when new data is recieved.
            recieveData();
            break;
        }
        case GBP_COMMAND_PRINT:
        { // This would usually indicate to the GBP to start printing.
            schedulePrint = true;
            break;
        }
        case GBP_COMMAND_INQUIRY:
        { // This is usally called multiple times to check if ready to print or has finished printing.

            break;
        }
        }

        digitalWrite(PIN_LED, HIGH);
        gbp_printer.packet_ready_flag = false; // Packet Processed
    }

    // Trigger Timeout and reset the printer if byte stopped being recieved.
    if ((gbp_printer.gbp_rx_tx_byte_buffer.syncronised))
    {
        if ((0 != gbp_printer.uptime_til_timeout_ms) && (millis() > gbp_printer.uptime_til_timeout_ms))
        { // reset printer byte and packet processor
            Serial.println("# ERROR: Timed Out");
            gbp_rx_tx_byte_reset(&(gbp_printer.gbp_rx_tx_byte_buffer));
            gbp_parse_message_reset(&(gbp_printer.gbp_packet_parser));
        }
    }
    else
    { // During scanning phase timeout is not required.
        gbp_printer.uptime_til_timeout_ms = 0;
    }

    // If new data recieved or button pushed, start print
    if (schedulePrint || !digitalRead(PIN_BTN))
    {
        bool w = false;
        if (!digitalRead(PIN_BTN))
        {
            w = true;
        }
        print();
        if (w)
        {
            delay(2000);
        }
    }
}

/**
 * Prints the data in the buffer
 */
void print()
{
    epson_linespacing(24);

    if (totalBytes == 0)
    {
        return;
    }

    epson_center();

    Serial.println("Data recieved, begin print!");

    if (method == GS_PRINT_METHOD)
    {
        if (scale < 3)
        {
            if (baudRate == FAST_BAUD_RATE)
            {
                printGsl();
            }
            else
            {
                printGsv0();
            }
        }
        else
        {
            gsXlPrint();
        }
    }
    else
    {
        if (scale == 2)
        {
            printEscAsterisk2x();
        }
        else if (scale == 3)
        {
            printEscAsterisk3x();
        }
    }

    epson_feed(7);

    if (cut)
    {
        if (method == ESC_PRINT_METHOD)
        {
            epson_feed(4);
        }
        epson_cut();
    }

    Serial.println("Print finished");
    gbp_printer.uptime_til_pretend_print_finish_ms = 0;
    gbp_printer.gbp_printer_status.printer_busy = false;
    digitalWrite(PIN_LED, HIGH);

#if SEND_TO_PC_AFTER_PRINTING
    sendBufferToPc();
#endif
}

/**
 * Print by "ESC *" method
 * 3x scale
 * https://reference.epson-biz.com/modules/ref_escpos/index.php?content_id=88
 */
void printEscAsterisk3x()
{
    epson_center();

    int imgWidth = IMG_WIDTH * 3;
    byte lineBuffer[IMG_WIDTH] = {};

    // line is 8 pixels high (by using 8 dot density is scaled internaly by the printer itself)
    for (byte line = 0; line < IMG_HEIGHT / 8; line++)
    {
        digitalWrite(PIN_LED, ((line % 2) == 0) ? HIGH : LOW);
        byte lbi = 0;
        // store in buffer for faster sending
        for (byte column = 0; column < IMG_WIDTH; column++)
        {
            byte data = 0;
            for (byte y = 0; y < 8; y++)
            {
                data = (data << 1) | bitRead(printBuffer[20 * y + line * 160 + column / 8], 7 - (column % 8));
            }
            lineBuffer[lbi++] = data;
        }

        // send data
        epson_write(27);                   // ESC
        epson_write(42);                   // *
        epson_write(1);                    // 8-dot double density
        epson_write(imgWidth & 0xFF);      // nL
        epson_write(imgWidth >> 8 & 0xFF); // nH
        for (lbi = 0; lbi < IMG_WIDTH; lbi++)
        {
            // repeat column 3 times
            for (byte s = 0; s < 3; s++)
            {
                epson_write(lineBuffer[lbi]);
            }
        }
        epson_write(10); // LF
    }
}

/**
 * Print by "ESC *" method
 * 2x scale
 * https://reference.epson-biz.com/modules/ref_escpos/index.php?content_id=88
 */
void printEscAsterisk2x()
{
    epson_center();

    int imgWidth = IMG_WIDTH;
    byte lineBuffer[IMG_WIDTH * 3] = {};

    // line is 12 pixels high
    for (byte line = 0; line < IMG_HEIGHT / 12; line++)
    {
        digitalWrite(PIN_LED, ((line % 2) == 0) ? HIGH : LOW);
        unsigned int lbi = 0;
        for (byte column = 0; column < IMG_WIDTH; column++)
        {
            uint32_t data = 0;
            for (byte y = 0; y < 12; y++)
            {
                byte a = bitRead(printBuffer[20 * y + line * 12 * EPSON_BYTES_PER_LINE + column / 8], 7 - (column % 8));
                data = (((data << 1) | a) << 1) | a;
            }
            lineBuffer[lbi++] = data >> 16 & 0xff;
            lineBuffer[lbi++] = data >> 8 & 0xff;
            lineBuffer[lbi++] = data & 0xff;
        }

        // send data
        epson_write(27);                   // ESC
        epson_write(42);                   // *
        epson_write(32);                   // 24-dot single density
        epson_write(imgWidth & 0xFF);      // nL
        epson_write(imgWidth >> 8 & 0xFF); // nH
        for (unsigned int i = 0; i < lbi; i++)
        {
            epson_write(lineBuffer[i]);
        }
        epson_write(10); // LF
    }
}

/**
 * Begins the print (scale: 1x, 2x)
 * https://reference.epson-biz.com/modules/ref_escpos/index.php?content_id=99#gs_lparen_cl_fn112
 */
void printGsl()
{
    unsigned int payload = BUFFER_SIZE + 10; // pL and pH specify the number of bytes following m as (pL + pH × 256).
    epson_write(29);                         // GS
    epson_write(40);                         // (
    epson_write(76);                         // L
    epson_write(payload & 0xFF);             // pL
    epson_write(payload >> 8 & 0xFF);        // pH
    epson_write(48);                         // m
    epson_write(112);                        // fn
    epson_write(48);                         // a
    epson_write(scale);                      // bx
    epson_write(scale);                      // by
    epson_write(49);                         // c
    epson_write(IMG_WIDTH & 0xFF);           // xL
    epson_write(IMG_WIDTH >> 8 & 0xFF);      // xH
    epson_write(IMG_HEIGHT & 0xFF);          // yL
    epson_write(IMG_HEIGHT >> 8 & 0xFF);     // yH

    sendBuffer();
    finishPrint();
}

/**
 * Begins the print - method for older printers (scale: 1x, 2x)
 * https://reference.epson-biz.com/modules/ref_escpos/index.php?content_id=94
 */
void printGsv0()
{
    epson_write(29);                          // GS
    epson_write(118);                         // v
    epson_write(48);                          // 0
    epson_write(scale == 2 ? 51 : 48);        // m (scale)
    epson_write((IMG_WIDTH / 8) & 0xFF);      // xL
    epson_write((IMG_WIDTH / 8) >> 8 & 0xFF); // xH
    epson_write(IMG_HEIGHT & 0xFF);           // yL
    epson_write(IMG_HEIGHT >> 8 & 0xFF);      // yH

    sendBuffer();
}

/**
 * Sends the whole buffer to the printer
 */
void sendBuffer()
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        digitalWrite(PIN_LED, ((i % 60) < 10) ? HIGH : LOW);
        epson_write(printBuffer[i]);
    }
}

/** 
 * Sends a command to print all data in printer's buffer
 *https://reference.epson-biz.com/modules/ref_escpos/index.php?content_id=98
 */
void finishPrint()
{
    epson_write(29); // GS
    epson_write(40); // (
    epson_write(76); // L
    epson_write(2);  // pL
    epson_write(0);  // pH
    epson_write(48); // m
    epson_write(50); // fn
}

/*
 * Provides 3x scaled print
 * since TM-T88 doesn't have big enough buffer for 3x scaled image, it must be sent in batches
 */
void gsXlPrint()
{
    Serial.println("Begin xl print");
    for (byte base = 0; base < IMG_HEIGHT; base += LINES_AT_ONCE_XL)
    {
        if (baudRate == FAST_BAUD_RATE)
        {
            gsXlPrintBeginGsl();
        }
        else
        {
            gsXlPrintBeginGsv0();
        }
        for (byte l = 0; l < LINES_AT_ONCE_XL; l++)
        {
            byte line = base + l;
            for (byte y = 0; y < scale; y++) // copy each line
            {
                for (byte x = 0; x < EPSON_BYTES_PER_LINE; x++) // for each pixel in line
                {
                    int i = line * EPSON_BYTES_PER_LINE + x;
                    uint32_t out = bitscale(printBuffer[i], 3);

                    byte currentBuffer[3] = {out >> 16 & 0xFF, out >> 8 & 0xFF, out & 0xFF};
                    for (byte b = 0; b < 3; b++)
                    {
                        epson_write(currentBuffer[b]);
                    }
                    digitalWrite(PIN_LED, ((i % 60) < 10) ? HIGH : LOW);
                }
            }
        }
        if (baudRate == FAST_BAUD_RATE)
        {
            finishPrint();
        }
    }
}

/**
 * Starts scaled print batch
 */
void gsXlPrintBeginGsl()
{
    unsigned int w = IMG_WIDTH * 3;
    unsigned int h = LINES_AT_ONCE_XL * 3;
    unsigned int payload = w / 8 * h + 10;
    epson_write(29);                  // GS
    epson_write(40);                  // (
    epson_write(76);                  // L
    epson_write(payload & 0xFF);      // pL
    epson_write(payload >> 8 & 0xFF); // pH
    epson_write(48);                  // m
    epson_write(112);                 // fn
    epson_write(48);                  // a
    epson_write(1);                   // bx
    epson_write(1);                   // by
    epson_write(49);                  // c
    epson_write(w & 0xFF);            // xL
    epson_write(w >> 8 & 0xFF);       // xH
    epson_write(h);                   // yL
    epson_write(0);                   // yH
}

/**
 * Starts scaled print batch
 * method for older printers
 */
void gsXlPrintBeginGsv0()
{
    unsigned int w = IMG_WIDTH * 3;
    unsigned int h = LINES_AT_ONCE_XL * 3;
    epson_write(29);                  // GS
    epson_write(118);                 // v
    epson_write(48);                  // 0
    epson_write(48);                  // m (scale)
    epson_write((w / 8) & 0xFF);      // xL
    epson_write((w / 8) >> 8 & 0xFF); // xH
    epson_write(h);                   // yL
    epson_write(0);                   // yH
}

/**
 * Clears the print buffer
 */
void clearBuffer()
{
    totalBytes = 0;
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        printBuffer[i] = 0;
    }
}

/** 
 * Recieves the data from the Game Boy and transforms it for the printer
 * 2-bit depth 8*8 tiles -> 1-bit depth in line pixels
 */
void recieveData()
{
    Serial.println("Recieving data...");
    byte lines = gbp_printer.gbp_packet.data_length / 16 / 20; //2
    for (int line = 0; line < lines; line++)
    {
        for (byte tile = 0; tile < TILES_PER_LINE; tile++)
        {
            for (byte j = 0; j < TILE_PIXEL_HEIGHT; j++)
            {
                for (byte i = 0; i < TILE_PIXEL_WIDTH; i++)
                {
                    short offset = tile * 8 + j + 8 * TILES_PER_LINE * line;
                    byte hiBit = (byte)((gbp_printer.gbp_packet.data_ptr[offset * 2 + 1] >> (7 - i)) & 1);
                    byte loBit = (byte)((gbp_printer.gbp_packet.data_ptr[offset * 2] >> (7 - i)) & 1);
                    byte val = (byte)((hiBit << 1) | loBit); // 0-3
                    int index = (tile + TILES_PER_LINE * j) + totalBytes;
                    if (val > 1)
                    {
                        printBuffer[index] = printBuffer[index] | (1 << (7 - i));
                    }
                }
            }
        }
        totalBytes += TILES_PER_LINE * 8;
    }
}

/**
 * Updates the setting based on DIP switches
 */
void updateDipSwitches()
{
    scale = !digitalRead(PIN_DIP_SCALE) ? 3 : 2;
    cut = !digitalRead(PIN_DIP_CUT);
    unsigned long oldBaudRate = baudRate;
    baudRate = !digitalRead(PIN_DIP_BAUDRATE) ? FAST_BAUD_RATE : SLOW_BAUD_RATE;
    method = !digitalRead(PIN_DIP_METHOD) ? GS_PRINT_METHOD : ESC_PRINT_METHOD;
    if (oldBaudRate != baudRate)
    {
        epson_start();
    }
}

/**
 * Prints a test
 */
void printerTest()
{
    epson_linespacing(30);
    epson_println("xbpxl ready");
    epson_feed(1);
    epson_print("baud rate: ");
    epson_println(baudRate);
    epson_print("scale: ");
    epson_println(scale);
    epson_print("method: ");
    if (method == ESC_PRINT_METHOD)
    {
        epson_println("ESC *");
    }
    else
    {
        if (baudRate == FAST_BAUD_RATE)
        {
            epson_println("GS ( L");
        }
        else
        {
            epson_println("GS v 0");
        }
    }
    epson_feed(2);
    epson_cut();
}

/**
 * Starts the printer
 * https://reference.epson-biz.com/modules/ref_escpos/index.php?content_id=192#esc_atsign
 */
void epson_start()
{
    if (Serial1)
    {
        Serial1.end();
        delay(200);
    }
    Serial1.begin(baudRate);

    // reset printer
    Serial1.write(27); // ESC
    Serial1.write(64); // @
}

/**
 * Justifies content center
 * https://www.epson-biz.com/modules/ref_escpos/index.php?content_id=58
 */
void epson_center()
{
    Serial1.write(0x1B);
    Serial1.write(0x61);
    Serial1.write(1);
}

/**
 * Espon line spacing
 */
void epson_linespacing(byte spacing)
{
    epson_write(27); // ESC
    epson_write(51); // 3
    epson_write(spacing);
}

/**
 * Feeds a number of lines
 */
void epson_feed(byte lines)
{
    Serial1.write(0x1B);
    Serial1.write(0x64);
    Serial1.write(lines);
}

/**
 * Sends a CUT command
 * https://www.epson-biz.com/modules/ref_escpos/index.php?content_id=87
 */
void epson_cut()
{
    Serial1.write(0x1D);
    Serial1.write(0x56);
    Serial1.write(cutMode);
    Serial1.write(0xA);
}

/**
 * Sends a single byte
 */
void epson_write(byte c)
{
    Serial1.write(c);
}

/**
 * Prints a text string
 */
size_t epson_println(const char *str)
{
    return Serial1.println(str);
}

/**
 * Prints a number
 */
size_t epson_println(unsigned long num)
{
    return Serial1.println(num);
}

/**
 * Prints a text string
 */
size_t epson_print(const char *str)
{
    return Serial1.print(str);
}

/**
 * Prints a number
 */
size_t epson_print(unsigned long num)
{
    return Serial1.print(num);
}

/**
 * Copies each bit in source byte to the destination uint32 "by" times
 * by = 3 in this program
 * example:
 * src: 000000000000000010010011
 * dst: 111000000111000000111111
 */
uint32_t bitscale(uint8_t src, uint8_t by)
{
    uint32_t dst;
    for (int8_t i = 7; i >= 0; i--)
    {
        for (uint8_t j = 0; j < by; j++)
        {
            dst = dst << 1 | ((src & 1 << i) >> i);
        }
    }
    return dst;
}

/**
 * Sends the buffer contents to the PC via Serial
 */
void sendBufferToPc()
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        if (i % 16 == 0)
        {
            Serial.println("");
        }
        digitalWrite(PIN_LED, ((i % 60) < 10) ? HIGH : LOW);
        Serial.print("0x");
        if (printBuffer[i] < 0x10)
        {
            Serial.print("0");
        }
        Serial.print(printBuffer[i], HEX);
        Serial.print(", ");
    }
}

/**
 * Copies test_image to buffer at the start
 */
void copyTestImageToBuffer()
{
    for (int i = 0; i < BUFFER_SIZE; i++)
    {
        printBuffer[i] = testImage[i];
    }
    totalBytes = BUFFER_SIZE;
    Serial.println("Test image copied to buffer");
}
