#include<WiFi.h>
#include<firebaseESP32.H>
#include <common.h>
#include <FirebaseESP32.h>
#include <FirebaseFS.h>
#include <Utils.h>

/*Constantes*/
const char* WIFI_SSID = "belisarius";
const char* WIFI_PW = "senha";

const char* FB_HOST = "https://iotmaria-default-rtdb.firebaseio.com/";
const char* FB_KEY = "wrJZTN9pGimlbgEtc4IuS1TV7HdNZhJfRPvCoLum";

/*Variaveis*/
FirebaseData fbdo;
FirebaseAuth fbauth;
FirebaseConfig fbconfig;

/*Funções*/
bool connectWiFi(const char* ssid, const char* pw)
{
  WiFi.mode(WIFI_STA); //modo estático, não muda o IP
  WiFi.disconnect();

  int qtde_wifi = WiFi.scanNetworks(); //retorna um int com o número de rede disponíveis

  if(qtde_wifi == 0)
  {
    return;
  }

  WiFi.begin(WIFI.SSID,WIFI_PW); //iniciliza uma rede Wifi

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

void setup() 
{
  Serial.begin(115200);
  connectWiFi(WIFI_SSID, WIFI_PW);

  // conectando banco de dados
  fbconfig.database_url = FB_HOST;
  fbconfig.signer.tokens.legacy_token = FB_KEY; 
  fbdo.setBSSLBufferSize(4096, 1024);
  Firebase.reconnectWiFi(true);
  Firebase.begin(&fbconfig, &fbauth);
}

void loop() 
{

  float value = 3.14;

  bool status = Firebase.setFloat(fbdo, "/iotmaria/valor", value);

  if(!status)
  {
    Serial.println(fbdo.errorReason().c_str());
  }
  delay(5000);
}
