#include <WiFi.h>
#include <FirebaseESP32.h>
#include <vector>

template<class T> // T representa o nome de tipo, template passa informações no tempo de compilação
using Vector = std::vector<T>; // <T> tipo generico

const uint8_t PIN_NTC_1 = 34;
const uint8_t PIN_NTC_2 = 35;
const uint8_t PIN_LDR = 32;

const uint32_t  ADC_MAX = (1 << 12) - 1;
const float VREF = 3.3f;
const float R1 = 10000.0f;

const Vector<float> NTC_10K_temp = { -55, -50, -45, -40, -35,
                               -30, -25, -20, -15, -10,
                               -5, 0, 5, 10, 15,
                               20, 25, 30, 35, 40,
                               45, 50, 55, 60, 65,
                               70, 75, 80, 85, 90,
                               95, 100, 105, 110, 115,
                               120, 125 };
 
const Vector<float> NTC_10K_res = { 1214600, 844390, 592430, 419380, 299480,
                              215670, 156410, 114660, 84510, 62927,
                              47077, 35563, 27119, 20860, 16204,
                              12683, 10000, 7942, 6327, 5074,
                              4103, 3336, 2724, 2237, 1846,
                              1530, 1275, 1068, 899.3, 760.7,
                              645.2, 549.4, 470.0, 403.6, 347.4,
                              300.1, 260.1 };

const char* WIFI_SSID = "Shrek";
const char* WIFI_PWD = "chorameliga";

const char* FB_HOST = "https://iiot-dta-default-rtdb.firebaseio.com/";
const char* FB_KEY = "Ag5gJMhAnTWQgDVhegkDRF1uTjJfpMUDkXB8WBEa";

FirebaseData fbdo;
FirebaseAuth fbauth;
FirebaseConfig fbconfig;

bool connectWiFi(const char* ssid, const char* pwd)
{
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, pwd);

  uint8_t current_trial = 0;
  
  Serial.print("Conectando");
  while(WiFi.status() != WL_CONNECTED)
  {
    current_trial++;

    if (current_trial > 300)
    {
      return false;
    }
    
    Serial.print(".");
    delay(200);
  }
  Serial.println();
  Serial.println("Conectado!");

  Serial.print("Conectado com o IP: ");
  Serial.println(WiFi.localIP());

  return true;
}

void connectFirebase(const char* fb_host, const char* fb_key)
{
  fbconfig.database_url = fb_host;
  fbconfig.signer.tokens.legacy_token = fb_key;
  
  fbdo.setBSSLBufferSize(4096, 1024);
  
  Firebase.reconnectWiFi(true);
  Firebase.begin(&fbconfig, &fbauth);
}

float getADCRead(uint8_t pin)
{
  uint16_t input_value = analogRead(pin);
  float voltage = static_cast<float>(input_value) * VREF / static_cast<float>(ADC_MAX);

  return voltage;
}

float getADCTemperature(uint8_t pin)
{
  float voltage = getADCRead(pin);
  float resistance = R1 * voltage / (VREF - voltage);
  int index;

  for(uint16_t i=0; i < NTC_10K_res.size() ; i++)
  {
    if(resistance > NTC_10K_res[i])
    {
      index = i;
      break;
    }
  }
  
  float temperature = NTC_10K_temp[index]+ (resistance - NTC_10K_res[index])*(NTC_10K_temp[index]-NTC_10K_temp[index-1])/(NTC_10K_res[index]-NTC_10K_res[index-1]);

  return temperature;
}

void setup()
{
  Serial.begin(115200);
  connectWiFi(WIFI_SSID, WIFI_PWD);
  connectFirebase(FB_HOST, FB_KEY);

  pinMode(PIN_NTC_1, INPUT);
  pinMode(PIN_NTC_2, INPUT);
  pinMode(PIN_LDR, INPUT);
}

void loop()
{
  float voltage_ntc_1 = getADCTemperature(PIN_NTC_1);
  float voltage_ntc_2 = getADCTemperature(PIN_NTC_2);
  float voltage_ldr = getADCRead(PIN_LDR);

  FirebaseJson json;
  json.set("/maquina1/temperatura/value1", voltage_ntc_1);
  json.set("/maquina1/temperatura/value2", voltage_ntc_2);
  json.set("/maquina1/luminosidade/value1", voltage_ldr);

  if (Firebase.updateNode(fbdo, "iiot-dta/subsys_05", json))
  {
    Serial.println("Dado salvo com sucesso!");
  }
  else
  {
    Serial.print("Falha: ");
    Serial.println(fbdo.errorReason().c_str());
  }

  delay(10000);
}
