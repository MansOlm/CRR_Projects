#include <Arduino.h>

const uint8_t led = 4;
const uint8_t btn = 5;

uint16_t voltage[7];
uint8_t adc_pin;

void analog_read(uint8_t pin)
{
  if (pin > 7)
    return;
  //Aktiverar den givna ADC pinnen (0-7)
  ADMUX |= pin;
  //Aktivera ADC:n
  ADCSRA |= _BV(ADEN);
  //Aktivera golbala interupts
  sei();
  //Interupt ska göras när ADC:n är klar
  ADCSRA |= _BV(ADIE);
  //Satrta konvertering på vald pin
  ADCSRA |= _BV(ADSC);
}

void analog_read_all()
{
  for (uint8_t i = 0; i < 7; i++)
  {
    adc_pin = i;
    analog_read(i);
    //Vänta tills nuvarande konvertiring är klar.
    uint8_t running = (ADCSRA & (1 << ADSC)) >> ADSC;
    while (running)
    {
      uint8_t running = (ADCSRA & (1 << ADSC)) >> ADSC;
    }
  }
}

ISR(ADC_vect)
{
  //Ge voltage på plats adc_pin det nyss konverterade värdet.
  voltage[adc_pin] = (ADCH << 9) + ADCL;
}

void setup()
{
  //BTN PINS
  DDRE = ~_BV(btn) & DDRE;
  PORTE = _BV(btn) | PORTE;

  //Led Pins
  DDRE = _BV(led) | DDRE;
  PORTE = ~_BV(led) & PORTE;
}

void loop()
{
  //Reading from BTN pin
  int btn_v = (PINE & _BV(btn)) >> btn;

  if (btn_v == 1)
  {
    PORTE = _BV(led) | PORTE;
  }
  else
  {
    PORTE = ~_BV(led) & PORTE;
  }
  analog_read_all();
  //läser alla analoga portar och lägger dess värde i voltage arrayen;
}