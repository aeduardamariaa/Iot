const uint8_t PIN_BUTTON = 21;
const uint8_t PIN_LED = 26;

/*---------Variaveis------------*/
bool led_state = LOW;
bool pressionado = LOW;
bool botao_anterior = LOW;
long tempo = 0;

void setup() 
{
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_LED, OUTPUT);

  digitalWrite(PIN_LED, LOW);

  Serial.begin(115200);//inicializa comunicação via USB, e passa o valor da velocidade da comunicação 
}

void loop() 
{
  botao_anterior = pressionado;
  pressionado = digitalRead(PIN_BUTTON);

  if(pressionado && !botao_anterior && (millis() - tempo > 50))
  {
    led_state = !led_state;
    digitalWrite(PIN_LED, led_state);
    tempo = millis();
  }

    Serial.println(led_state); // manda que pula de linha 
}
