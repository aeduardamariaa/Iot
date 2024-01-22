// const uint8_t PIN_BUTTON = 26;

// /*---------Variaveis------------*/
// bool pressionado = LOW;
// bool botao_anterior = LOW;
// long tempo = 0;

// void setup() 
// {
//   pinMode(PIN_BUTTON, INPUT);

//   Serial.begin(115200);//inicializa comunicação via USB, e passa o valor da velocidade da comunicação 
// }

// void loop() 
// {
//   botao_anterior = pressionado;
//   pressionado = digitalRead(PIN_BUTTON);

//   if(pressionado && !botao_anterior && (millis() - tempo > 50))
//   {
//     Serial.println("Bom dia!");
//   }

//     Serial.println(pressionado); // manda que pula de linha 
// }


#include "BluetoothSerial.h"
#include <Arduino.h>

const uint8_t PIN_BUTTON1 = 26;
const uint8_t PIN_BUTTON2 = 27;

BluetoothSerial SerialBT;

void enviarDadosBluetooth(bool botao_1, bool botao_2) {

    // Construir os bytes para envio
    byte dados[2];
    dados[0] = botao_1;
    dados[1] = botao_2;

    // Enviar dados via Bluetooth
    SerialBT.write(dados, 2);
}

void setup() 
{
  pinMode(PIN_BUTTON1, INPUT);
  pinMode(PIN_BUTTON2, INPUT);

  Serial.begin(115200);
  SerialBT.begin("esp32bt");
  Serial.println("Started!");
}

void loop() 
{
  bool pressionado_1 = digitalRead(PIN_BUTTON1);
  bool pressionado_2 = digitalRead(PIN_BUTTON2);

  Serial.printf("BOTÃO 1: %d\nBOTÃO 2 %d\n\n", pressionado_1, pressionado_2);
  
  enviarDadosBluetooth(pressionado_1, pressionado_2);
  
  delay(2000);
}
