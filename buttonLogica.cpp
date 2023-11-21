const uint8_t PIN_BUTTON = 21;
const uint8_t PIN_LED = 26;

/*---------Variaveis------------*/
bool led_state = LOW;
bool botao_anterior;


void setup() 
{
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED, OUTPUT);

  digitalWrite(PIN_LED, LOW);
  
}

void loop() 
{
  bool pressionado = digitalRead(PIN_BUTTON);


  if(pressionado && !botao_anterior)
  {
    led_state = !led_state;
    digitalWrite(PIN_LED, led_state);
  }
}
