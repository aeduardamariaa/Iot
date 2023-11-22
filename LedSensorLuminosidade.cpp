#include<Arduino.h>

//pino
const uint8_t PIN_INPUT = 25;
const uint8_t PIN_LED = 26;

//constatnte
const uint32_t  ADC_MAX = 4095;
const float VREF = 3.3f;

void setup()
{
  pinMode(PIN_INPUT, INPUT);
  pinMode(PIN_LED, OUTPUT);

  Serial.begin(115200);//inicializa comunicação via USB, e passa o valor da velocidade da comunicação 
}

void loop()
{
  uint16_t input_value = analogRead(PIN_INPUT);
  float tensao = static_cast<float>(input_value) * VREF / static_cast<float>(ADC_MAX); //divisão de int por int retorna inteiro

  if (tensao > 1.7)
  {
    digitalWrite(PIN_LED, HIGH);
  }
  else
  {
    digitalWrite(PIN_LED, LOW);
  }
  
  // Serial.print(); // manda string
  // Serial.write(); // manda 1 char
  Serial.println(tensao); // manda que pula de linha 
}
