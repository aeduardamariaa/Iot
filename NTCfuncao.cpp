#include <vector>
#include <cmath>
#include <Arduino.h>

template<class T> // T representa o nome de tipo, template passa informações no tempo de compilação
using Vector = std::vector<T>; // <T> tipo generico
 
const uint8_t PIN_NTC = 26;

const uint32_t ADC_MAX = (1 << 12) - 1;
const float VREF = 3.3f;
const float R1 = 10000.0f;
 

void setup()
{
  pinMode(PIN_NTC, INPUT);
  Serial.begin(115200);
}

void loop()
{
  uint16_t input_value = analogRead(PIN_NTC);

  float voltage = input_value * VREF / ADC_MAX;

  float resistance = R1 * voltage / (VREF - voltage);

  // int index;

  // for(uint16_t i=0; i < NTC_10K_res.size() ; i++)
  // {
  //   if(resistance > NTC_10K_res[i])
  //   {
  //     index = i;
  //     break;
  //   }
  // }
  float a = -19.49123972;
  float b = 204.88328885;
  float c = 208.78577114;
  float temperature = a * log(resistance - b) + c;

  Serial.printf("ADC: %8i \nVoltage: %8.2f \nResistance: %8.2f \nTemperature: %8.2f\n\n",
    input_value, voltage, resistance, temperature);
  
  delay(3000);
}
