// --------------------------------------
// i2c_scanner
//
// Version 1
//    This program (or code that looks like it)
//    can be found in many places.
//    For example on the Arduino.cc forum.
//    The original author is not know.
// Version 2, Juni 2012, Using Arduino 1.0.1
//     Adapted to be as simple as possible by Arduino.cc user Krodal
// Version 3, Feb 26  2013
//    V3 by louarnold
// Version 4, March 3, 2013, Using Arduino 1.0.3
//    by Arduino.cc user Krodal.
//    Changes by louarnold removed.
//    Scanning addresses changed from 0...127 to 1...119,
//    according to the i2c scanner by Nick Gammon
//    https://www.gammon.com.au/forum/?id=10896
// Version 5, March 28, 2013
//    As version 4, but address scans now to 127.
//    A sensor seems to use address 120.
// Version 6, November 27, 2015.
//    Added waiting for the Leonardo serial communication.
//
//
// This sketch tests the standard 7-bit addresses
// Devices with higher bit address might not be seen properly.
//

#include <Arduino.h>
#include <Wire.h>

void setup()
{
  Wire.begin();

  Serial.begin(9600);
  while (!Serial)
    ; // Leonardo: wait for serial monitor
  Serial.println("\nI2C Scanner");
}

void loop()
{
  byte error, address;
  int nDevices;

  Serial.println("Scanning...");

  nDevices = 0;
  for (address = 1; address < 127; address++)
  {
    // The i2c_scanner uses the return value of
    // the Write.endTransmisstion to see if
    // a device did acknowledge to the address.
    Wire.beginTransmission(address);
    error = Wire.endTransmission();

    if (error == 0)
    {
      Serial.print("I2C device found at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.print(address, HEX);
      Serial.println("  !");

      nDevices++;
    }
    else if (error == 4)
    {
      Serial.print("Unknown error at address 0x");
      if (address < 16)
        Serial.print("0");
      Serial.println(address, HEX);
    }
  }
  if (nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");

  delay(5000); // wait 5 seconds for next scan
}

// #include <Arduino.h>
// #include <Wire.h>
// #include "throttleControl.h"

// const uint8_t V1 = A0;
// const uint8_t V2 = A1;

// float volt1;
// float volt2;

// static const uint16_t SECOND_BYTE = 65280;
// static const uint8_t FIRST_BYTE = 255;
// static const uint16_t MID_BYTE = 4080;
// static const uint8_t HALF_BYTE = 15;

// static const uint8_t MCP0 = 0x62;
// static const uint8_t MCP1 = 0x63;

// void setVolt(uint8_t adress, uint16_t volt)
// {

//   volt = volt & 4095;

//   uint8_t b0 = B01000000;
//   uint8_t b1 = (volt & MID_BYTE) >> 4;
//   uint8_t b2 = (volt & HALF_BYTE);

//   Wire.beginTransmission(adress);
//   Wire.write(b0);
//   Wire.write(b1);
//   Wire.write(b2);
//   Wire.endTransmission();
// }

// void setup()
// {
//   Serial.begin(9600);
//   Wire.begin();
//   pinMode(V2, INPUT);
//   pinMode(V2, INPUT);
// }

// int v = 0;

// void loop()
// {
//   setVolt(MCP0, v);
//   setVolt(MCP1, v);

//   volt1 = 5.0 / (1 << 10) * analogRead(V1);
//   volt2 = 5.0 / (1 << 10) * analogRead(V2);

//   Serial.print("Right: ");
//   Serial.print(volt1);
//   Serial.print("    ");
//   Serial.print("Left: ");
//   Serial.println(volt2);

//   delay(100);
// }
