// TX_PUSHBUTTON
#include <SPI.h>

#define CAN_2515
#define pushButton  7
// #define CAN_2518FD

// Set SPI CS Pin according to your hardware

#if defined(SEEED_WIO_TERMINAL) && defined(CAN_2518FD)
// For Wio Terminal w/ MCP2518FD RPi Hat：
// Channel 0 SPI_CS Pin: BCM 8
// Channel 1 SPI_CS Pin: BCM 7
// Interupt Pin: BCM25
const int SPI_CS_PIN  = BCM8;
const int CAN_INT_PIN = BCM25;
#else

// For Arduino MCP2515 Hat:
// the cs pin of the version after v1.1 is default to D9
// v0.9b and v1.0 is default D10
const int SPI_CS_PIN = 53;
const int CAN_INT_PIN = 2;
#endif


#ifdef CAN_2518FD
#include "mcp2518fd_can.h"
mcp2518fd CAN(SPI_CS_PIN); // Set CS pin
#endif

#ifdef CAN_2515
#include "mcp2515_can.h"
mcp2515_can CAN(SPI_CS_PIN); // Set CS pin
#endif

const int ledHIGH    = 1;
const int ledLOW     = 0;
                           

void setup() {
    SERIAL_PORT_MONITOR.begin(115200);

    while (CAN_OK != CAN.begin(CAN_500KBPS)) {             // init can bus : baudrate = 500k
        SERIAL_PORT_MONITOR.println("CAN init fail, retry...");
        delay(100);
    }
    SERIAL_PORT_MONITOR.println("CAN init ok!");
}

unsigned char stmp[8] = {0, 0, 2, 3, 4, 5, 6, 7};

void loop() {
    SERIAL_PORT_MONITOR.println("In loop");

int  buttonState = digitalRead(pushButton);
  // Create a 4-bit value (bits 3 to 0) representing the pushbutton state (1 when pressed, 0 when released)
    byte dataToSend = (buttonState << 4) & 0X0F; // Keep only the lower bit (bit 0)
    byte data = (buttonState) & 0x0f;
    stmp[0] = dataToSend;
    stmp[1] = data;
    // send data:  id = 0x70, standard frame, data len = 8, stmp: data buf
    CAN.MCP_CAN::sendMsgBuf(0x70, 0, 8, stmp);
    
    delay(1000);                       // send data once per second
}

/*********************************************************************************************************
    END FILE
*********************************************************************************************************/
