#include <Arduino.h>
#include <SPI.h>
#include "mcp2515_can.h"
#include "CAN.h"

mcp2515_can CAN(SPI_CS_PIN);

void CANSetup()
{
    while (CAN_OK != CAN.begin(CAN_500KBPS))
    { // init can bus : baudrate = 500k
        Serial.println("CAN init fail, retry...");
        delay(100);
    }
}

void sendFrame(uint32_t id, uint8_t ext, uint8_t len, uint8_t *frames)
{
    CAN.sendMsgBuf(id, ext, len, frames);
}