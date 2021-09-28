#include <Arduino.h>
#include <SPI.h>
#include "mcp2515_can.h"

#ifndef CAN_2515
#define CAN_2515

const int SPI_CS_PIN = 9;
const int CAN_INT_PIN = 2;

//Public methods
void sendFrame(uint32_t id, uint8_t ext, uint8_t len, uint8_t *frames);
void CANSetup();

#endif