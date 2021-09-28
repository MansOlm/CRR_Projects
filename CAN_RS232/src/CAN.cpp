#include <Arduino.h>
#include <CAN.h>

static FlexCAN_T4<CAN1, RX_SIZE_256, TX_SIZE_16> Can0;

static uint16_t currentLimit = 0;
static const uint32_t CURRENT_ADRESS = 0x1807EFF3;

uint16_t getCurrentLimit()
{
    return currentLimit;
}

void reciveCurrentLimit(const CAN_message_t &msg)
{
    //Read the CAN message and set current limit to the given value
    currentLimit = msg.buf[0] << 8;
    currentLimit += msg.buf[1];

    CAN_message_t m;
    m.id = 0x13A43253;
    m.len = 2;
    for (int i = 0; i < 8; i++)
    {
        m.buf[i] = i;
    }

    Can0.write(msg);
    Serial.print("Reciev");
}

void canSetup()
{
    Can0.begin();
    Can0.setBaudRate(BAUD_RATE);
    Can0.setMaxMB(TX_MAILBOXES + RX_MAILBOXES);

    for (int i = 0; i < RX_MAILBOXES; i++)
    {
        Can0.setMB(i, RX, EXT);
    }

    for (int i = RX_MAILBOXES; i < (RX_MAILBOXES + TX_MAILBOXES); i++)
    {
        Can0.setMB(i, RX, EXT);
    }

    Can0.setMBFilter(REJECT_ALL);
    Can0.enableMBInterrupts();
    Can0.onReceive(MB0, reciveCurrentLimit);

    Can0.setMBFilter(MB0, CURRENT_ADRESS);
}

void status()
{
    Can0.mailboxStatus();
}

// void canSniff(const CAN_message_t &msg)
// {
//     Serial.print("MB ");
//     Serial.print(msg.mb);
//     Serial.print("  OVERRUN: ");
//     Serial.print(msg.flags.overrun);
//     Serial.print("  LEN: ");
//     Serial.print(msg.len);
//     Serial.print(" EXT: ");
//     Serial.print(msg.flags.extended);
//     Serial.print(" TS: ");
//     Serial.print(msg.timestamp);
//     Serial.print(" ID: ");
//     Serial.print(msg.id, HEX);
//     Serial.print(" Buffer: ");
//     for (uint8_t i = 0; i < msg.len; i++)
//     {
//         Serial.print(msg.buf[i], HEX);
//         Serial.print(" ");
//     }
//     Serial.println();
// }

// void sendR232()
// {
//     for (uint8_t i = 0; i < bufSize; i++)
//     {
//         Serial.write(recived[i]);
//     }
// }