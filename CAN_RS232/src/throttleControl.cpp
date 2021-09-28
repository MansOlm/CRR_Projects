#include <Arduino.h>
#include <Wire.h>
#include "throttleControl.h"

static const uint8_t POT1 = A1;
static const uint8_t POT2 = A0;

static const uint8_t MCP0 = 0x62;
static const uint8_t MCP1 = 0x63;

static const uint16_t SECOND_BYTE = 65280;
static const uint8_t FIRST_BYTE = 255;
static const uint16_t MID_BYTE = 4080;
static const uint8_t HALF_BYTE = 15;
static const uint16_t MAX_VOLT = 3103;

static uint16_t throt1;
static uint16_t throt2;
static uint16_t throt;

void throtSetup()
{
    analogReadResolution(ADC_ACCURICY);
    pinMode(POT1, INPUT);
    pinMode(POT2, INPUT);
}

uint16_t checkThrot(uint16_t t1, uint16_t t2)
{
    uint16_t big, small;

    if (t1 >= t2)
    {
        big = t1;
        small = t2;
    }
    else
    {
        big = t2;
        small = t1;
    }

    if (big - small < big * 0.1)
    {
        return small;
    }
    return 0;
}

uint16_t readPotentiometer(uint8_t pin)
{
    uint16_t v = analogRead(pin);
    if (v > MAX_VOLT)
    {
        v = MAX_VOLT;
    }
    return v * 6.6 / 5;
}

void setVoltSlow(uint8_t adress, uint16_t volt)
{

    volt = volt & 4095;

    uint8_t b0 = B01000000;
    uint8_t b1 = (volt & MID_BYTE) >> 4;
    uint8_t b2 = (volt & HALF_BYTE);

    Wire.beginTransmission(adress);
    Wire.write(b0);
    Wire.write(b1);
    Wire.write(b2);
    Wire.endTransmission();

    // Serial.print(adress);
    // Serial.print(" set to: ");
    // Serial.print(volt * 5.0 / 4096);
    // Serial.print("   ");
}

void setVoltFast(uint8_t adress, uint16_t volt)
{

    volt = volt & 4095;

    uint8_t b1 = (volt & SECOND_BYTE) >> 8;
    uint8_t b2 = (volt & FIRST_BYTE);

    Wire.beginTransmission(adress);
    Wire.write(b1);
    Wire.write(b2);
    Wire.endTransmission();

    // Serial.print(adress);
    // Serial.print(" set to: ");
    // Serial.print(volt * 5.0 / 4096);
    // Serial.print("   ");
}

void throttleSeq()
{
    throt1 = readPotentiometer(POT1);
    throt2 = readPotentiometer(POT2);

    // Serial.print("Throt1: ");
    // Serial.print(throt1);
    // Serial.print("    ");
    // Serial.print("Throt2: ");
    // Serial.println(throt2);

    throt = checkThrot(throt1, throt2);

    setVoltFast(MCP0, throt);
    setVoltFast(MCP1, throt);

    // Serial.println("");
    delay(500);
}