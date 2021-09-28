#include <Arduino.h>
const int led = LED_BUILTIN;
const int btn = 54;
void setup()
{
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
  pinMode(btn, INPUT);
}

void loop()
{
  int btn_pushed = digitalRead(btn);

  if (btn_pushed == 0)
  {
    digitalWrite(led, HIGH);
  }
  else
  {
    digitalWrite(led, HIGH);
  }
}