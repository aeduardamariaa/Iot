const uint8_t PIN_LEDS[] = {32,33,25,26};

void setup() {
  // put your setup code here, to run once:
  for(auto pino : PIN_LEDS)
  {
    pinMode(pino, OUTPUT);
  }
}

void loop() {
  for(uint8_t i=0; i<16; i++)
  {
    for (uint8_t j=0; j < 4; j++)
    {
      digitalWrite(PIN_LEDS[j],((i % (2 << j)) - (i % (1 << j))) > 0);
    }
    //digitalWrite(PIN_LEDS[0], (i % 2));
    //digitalWrite(PIN_LEDS[1], ((i % 2)-(i % 4))>0);
    //digitalWrite(PIN_LEDS[2], ((i % 8)-(i % 4))>0);
    //digitalWrite(PIN_LEDS[3], ((i % 16)-(i % 4))>0);
    delay(1000);
  }
}
