const uint8_t PIN_INPUT = 26;

const uint16_t  ADC_MAX = 4095;
const float VCC = 3.3;

void setup()
{
  pinMode(PIN_INPUT, INPUT);

  Serial.begin(115200);
}

void loop()
{
  int input = analogRead(PIN_INPUT);
  float tensao = static_cast<float>(input) input * VCC / ADC_MAX; //divisão de int por int retorna inteiro

  Serial.print(tensao); // manda string
  Serial.write(); // manda 1 char
  Serial.println(); // manda que pula de linha 
}
