const uint8_t PIN_BUTTON = 21;
const uint8_t PIN_LED = 26;

void setup() 
{
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED, OUTPUT);
}

void loop() 
{
  bool pressionado = digitalRead(PIN_BUTTON);

  digitalWrite(PIN_LED, pressionado);
}
