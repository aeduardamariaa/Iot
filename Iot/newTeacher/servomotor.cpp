#include<Servo.h>

Servo myServo;
int LED_VERMELHO = 11;
int LED_VERDE = 13;
int grau;

// VEMELHO ACENDE COM O MOTR GIRANDO
// VERDE ACENDE QUANDO O MOTOR TA PARADO
void setup()
{
  Serial.begin(9600);
  pinMode(LED_VERMELHO, OUTPUT);
  pinMode(LED_VERDE, OUTPUT);
  myServo.attach(9); // porta 9
}

void loop()
{
  digitalWrite(LED_VERMELHO, LOW);
  digitalWrite(LED_VERDE, HIGH);
  grau = 255;
  
  Serial.println("Informe o grau: ");
  myServo.write(0);
  
  while(Serial.available() == 0){
   
  }

  grau = Serial.parseInt();
  
   if(grau > 0 && grau < 181){
    	digitalWrite(LED_VERMELHO, HIGH);
    	digitalWrite(LED_VERDE, LOW);
     	myServo.write(grau);
     	delay(1000);
   }
}
