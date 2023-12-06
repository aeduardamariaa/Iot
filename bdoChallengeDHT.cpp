#include <WiFi.h>
#include <Arduino.h>
#include "PubSubClient.h"
#include "DHT.h"
#include <FirebaseESP32.h>

const uint8_t PIN_INPUT = 34;

const char* WIFI_SSID = "Vivo-Internet-BF17";
const char* WIFI_PW = "78814222";

const char* FB_HOST = "https://iiot-dta-default-rtdb.firebaseio.com/";
const char* FB_KEY = "Ag5gJMhAnTWQgDVhegkDRF1uTjJfpMUDkXB8WBEa";

FirebaseData fbdo;
FirebaseAuth fbauth;
FirebaseConfig fbconfig;

/*Constantes DHT 11 e DHT 22*/
#define DHTTYPE DHT11

/*Variaveis*/
DHT dht(PIN_INPUT, DHTTYPE);

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

float* readDHT()
{
  static float data[2];
  float humidade = dht.readHumidity();
  float temperatura = dht.readTemperature();

  if(isnan(humidade)|| isnan(temperatura))
  {
    Serial.println("Falha na leitura do sendor DHT");
    return NULL;
  }
  Serial.printf("Humidade: %4.2f\nTemperatura: %7.2f\n\n", humidade, temperatura);
  data[0] = humidade;
  data[1] = temperatura;

  delay(5000);
  return data;
}

void setup()
{
  dht.begin();
  connectWiFi(WIFI_SSID, WIFI_PW);

  Serial.begin(115200);//inicializa comunicação via USB, e passa o valor da velocidade da comunicação
  connectFirebase(FB_HOST, FB_KEY);
}

void loop()
{
  readDHT();
  float* data = readDHT();

  FirebaseJson json;

  json.set("/temperature", data[1]);
  json.set("/humidity", data[0]);

  if (Firebase.updateNode(fbdo, "challenge02/subsys_05/", json))
  {
    Serial.println("Dado salvo com sucesso!");
  }
  else
  {
    Serial.print("Falha: ");
    Serial.println(fbdo.errorReason().c_str());
  }
  delay(30000);
}
