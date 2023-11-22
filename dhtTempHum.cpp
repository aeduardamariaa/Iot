#include<Arduino.h>
#include "DHT.h"

const uint8_t PIN_INPUT = 26;

/*Constantes DHT 11 e DHT 22*/
#define DHTTYPE DHT11

/*Variaveis*/
DHT dht(PIN_INPUT, DHTTYPE);


void setup()
{
  dht.begin();

  Serial.begin(115200);//inicializa comunicação via USB, e passa o valor da velocidade da comunicação 
}

void loop()
{
  float humidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if(isnan(humidade)|| isnan(temperatura))
  {
    Serial.println("Falha na leitura do sendor DHT");
    return;
  }

  // Serial.print("Humidade: ");
  // Serial.println(humidade);
  // Serial.print("Temperatura: ");
  // Serial.println(temperatura);
  Serial.printf("Humidade: %4.2f\nTemperatura: %7.2f\n\n", humidade, temperatura);

  delay(2000);

}
