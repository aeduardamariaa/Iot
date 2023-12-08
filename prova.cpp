#include <WiFi.h>
#include <Arduino.h>
#include "PubSubClient.h"
#include <FirebaseESP32.h>
#include <string.h>
#include <vector>

template<class T> // T representa o nome de tipo, template passa informações no tempo de compilação
using Vector = std::vector<T>; // <T> tipo generico

const uint8_t PIN_NTC_1 = 32;
const uint8_t PIN_NTC_2 = 35;
const uint8_t PIN_LED_1 = 27;
const uint8_t PIN_LED_2 = 2;
const uint8_t PIN_LED_3 = 15;
const uint8_t PIN_LED_4 = 4;
const uint8_t PIN_BUTTON = 12;

const char* MQTT_BROKER = "test.mosquitto.org";
const int MQTT_PORT = 1883;
const char* MQTT_USERNAME = "";
const char* MQTT_PASSWORD = "";

const uint32_t  ADC_MAX = (1 << 12) - 1;
const float VREF = 3.3f;
const float R1 = 10000.0f;

bool pressionado = LOW;
bool botao_anterior = LOW;

const char* WIFI_SSID = "Vivo-Internet-BF17";
const char* WIFI_PW = "78814222";

const char* FB_HOST = "https://iiot-dta-default-rtdb.firebaseio.com/";
const char* FB_KEY = "Ag5gJMhAnTWQgDVhegkDRF1uTjJfpMUDkXB8WBEa";

FirebaseData fbdo;
FirebaseAuth fbauth;
FirebaseConfig fbconfig;

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

WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

bool connectWiFi(const char* ssid, const char* pw);
void connectFirebase(const char* fb_host, const char* fb_key);
float getADCRead(uint8_t pin);
float getADCTemperature(uint8_t pin);
void callback(char* topic, byte* payload, unsigned int length);

void setup()
{
  Serial.begin(115200);
  pinMode(PIN_LED_1, OUTPUT);
  pinMode(PIN_LED_2, OUTPUT);
  pinMode(PIN_LED_3, OUTPUT);
  pinMode(PIN_LED_4, OUTPUT);
  pinMode(PIN_BUTTON, INPUT);
  pinMode(PIN_NTC_1, INPUT);
  pinMode(PIN_NTC_2, INPUT);

  connectWiFi(WIFI_SSID, WIFI_PW);

  connectFirebase(FB_HOST, FB_KEY);

  mqtt_client.setServer(MQTT_BROKER, MQTT_PORT);
  mqtt_client.setCallback(callback);

  while (!mqtt_client.connected())
  {
    String client_id = "mqttx_32fef669";
    client_id += String(WiFi.macAddress());

    if(mqtt_client.connect(client_id.c_str(), MQTT_USERNAME, MQTT_PASSWORD))
    {
      Serial.println("Conexao MQTT bem sucedida");
    }
  }
  mqtt_client.subscribe("iiot-dta/check");
}

void loop()
{
  botao_anterior = pressionado;
  pressionado = digitalRead(PIN_BUTTON);

  float temperatura_ntc_1 = getADCTemperature(PIN_NTC_1);
  float temperatura_ntc_2 = getADCTemperature(PIN_NTC_2);

  float media = 0;
  float desvio_padrao = 0;

  FirebaseJson json;

  media = (temperatura_ntc_1 + temperatura_ntc_2) / 2;
  desvio_padrao = (temperatura_ntc_1 - temperatura_ntc_2) / 1.414;

  if(pressionado && !botao_anterior)
  {
    json.set("/media", media);
    json.set("/desvio_padrao", desvio_padrao);

    if (Firebase.updateNode(fbdo, "avaliacao/subsys_05/", json))
    {
      digitalWrite(PIN_LED_1, HIGH);
      Serial.println("Dado salvo com sucesso!");
    }
    else
    {
      Serial.print("Falha: ");
      Serial.println(fbdo.errorReason().c_str());
    }
    digitalWrite(PIN_LED_1, LOW);
  }

  Serial.printf("TEMP 1: %4.2f\nTemperatura: %7.2f\n\n", temperatura_ntc_1, temperatura_ntc_2);

  if (media >= 21 && media < 24) {
      digitalWrite(PIN_LED_2, HIGH);
  }else if (media >= 24 && media < 27){
      digitalWrite(PIN_LED_2, HIGH);
      digitalWrite(PIN_LED_3, HIGH);
  }else if(media >=27){
      digitalWrite(PIN_LED_2, HIGH);
      digitalWrite(PIN_LED_3, HIGH);
      digitalWrite(PIN_LED_4, HIGH);
  }else{
      digitalWrite(PIN_LED_2, LOW);
      digitalWrite(PIN_LED_3, LOW);
      digitalWrite(PIN_LED_4, LOW);
  }
  mqtt_client.loop();

  delay(2000);
}

bool connectWiFi(const char* ssid, const char* pw)
{
  WiFi.mode(WIFI_STA); //modo estático, não muda o IP
  WiFi.disconnect();

  int qtde_wifi = WiFi.scanNetworks(); //retorna um int com o número de rede disponíveis

  if(qtde_wifi == 0)
  {
    return false;
  }

  WiFi.begin(WIFI_SSID, WIFI_PW); //iniciliza uma rede Wifi

  Serial.print("Conectando");
  int tentativa = 0;

  while(WiFi.status() != WL_CONNECTED)
  {
    tentativa ++;

    if (tentativa > 300)
    {
      return false;
    }

    Serial.print(".");
    delay(200);
  }
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

void callback(char* topic, byte* payload, unsigned int length)
{
    Serial.printf("Mensagem recebida no topico: %s", topic);
    Serial.println();

    String menssage = "";

    for(uint16_t i=0; i < length; i++)
    {
      menssage += static_cast<char>(payload[i]);
    }
    Serial.println(menssage);

    if (strcmp(topic, "iiot-dta/check") == 0)
    {
      if (menssage == "100")
      {
        json.set("/media", media);
        json.set("/desvio_padrao", desvio_padrao);

        if (Firebase.updateNode(fbdo, "avaliacao/subsys_05/", json))
        {
          digitalWrite(PIN_LED_1, HIGH);
          Serial.println("Dado salvo com sucesso!");
        }
        else
        {
          Serial.print("Falha: ");
          Serial.println(fbdo.errorReason().c_str());
        }
        digitalWrite(PIN_LED_1, LOW);
      }
    }
    Serial.println();
}
