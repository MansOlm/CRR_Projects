#include <Arduino.h>
#include "CAN.h"
#include "throttleControl.h"

static const uint32_t CURRENT_ADRESS = 0x1807EFF3;

void setup()
{
  CANSetup();
  Serial.begin(115000);
}

uint8_t c_lim[2] = {0, 0};
uint8_t msg[] = {0, 0, 0, 0, 0, 0, 0, 0, 0};

void loop()
{
  // throttleSeq();

  // if (c_lim[1] <= 255)
  // {
  //   c_lim[1] += 5;
  // }
  // else
  // {
  //   c_lim[0] += 5;
  // }

  sendFrame(CURRENT_ADRESS, 1, 2, c_lim);

  delay(500);
}