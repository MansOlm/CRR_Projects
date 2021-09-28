#include <Arduino.h>
#include "motorCom.h"
#include "CAN.h"

static float throttleInput = 0;
static float breakInput = 0;
static float inputVoltage = 0;
static float phaseCurrent = 0;
static uint16_t RPM = 0;
static float controllerTemp = 0;
static float motorTemp = 0;

void RS232Setup()
{
    RS232.begin(RS232Baud);
    RS232.setTX(TX);
    RS232.setRX(RX);
}

void userDataToController()
{
    char c;
    while (Serial.available() > 0)
    {
        c = Serial.read();
        if (c == '+')
        {
            RS232.write('s');
            RS232.write('+');
        }
        else if (c == 'p')
        {
            RS232.write('p');
        }

        Serial.print("RS232 wrote: ");
        Serial.println(c);
    }
}

void readRS232()
{
    char c;
    while (RS232.available() > 0)
    {
        c = RS232.read();
        Serial.print("RS232 recived: ");
        Serial.println(c);
    }
}

void setCurrentLimit()
{
    char currentLimit[3];
    itoa(getCurrentLimit(), currentLimit, 3);

    Serial.write('a');

    Serial.write('c');
    Serial.write('l');

    Serial.write(currentLimit);

    Serial.write('e');
}

void readMotorStats()
{
    uint8_t id[3];
    char buff[5];
    uint8_t trash[3];

    if (Serial.available() > 0)
    {
        Serial.readBytesUntil('=', id, 3);
        Serial.read();

        switch (id[0])
        {
        case 'T':
            Serial.readBytes(buff, 5);
            throttleInput = atof(buff);
            break;

        case 'a':
            Serial.readBytes(buff, 5);
            breakInput = atof(buff);
            break;
        case 'P':
            Serial.readBytes(buff, 5);
            inputVoltage = atoi(buff);
            break;
        case 'U':
            Serial.readBytes(buff, 5);
            inputVoltage = atof(buff);
            break;
        case 'I':
            Serial.readBytes(buff, 5);
            phaseCurrent = atof(buff);
            break;
        case 'R':
            Serial.readBytes(buff, 5);
            RPM = atoi(buff);
            break;
        case 'c':
            Serial.readBytes(buff, 5);
            controllerTemp = atof(buff);
            break;
        case 'm':
            Serial.readBytes(buff, 5);
            motorTemp = atof(buff);
            break;

        default:
            break;
        }

        Serial.readBytesUntil(',', trash, 3);
        Serial.read();
    }
}