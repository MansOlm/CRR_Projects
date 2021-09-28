#include <Arduino.h>
#include <FlexCAN_T4.h>

#ifndef CAN_LIB
#define CAN_LIB

#define BAUD_RATE 500000
#define TX_MAILBOXES 2
#define RX_MAILBOXES 1

/*----------- PUBLIC METHODS ---------------*/
void canSetup();
void status();
uint16_t getCurrentLimit();

#endif