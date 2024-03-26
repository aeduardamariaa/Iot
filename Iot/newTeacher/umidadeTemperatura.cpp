#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define I2C_ADDR 0x27

#define LCD_COLS 16
#define LCD_ROWS 2

#define UMIDADE_SOLO_PIN A1

const int temp_pin = A0;
float voltage, tempC;

LiquidCrystal_I2C lcd(I2C_ADDR, LCD_COLS, LCD_ROWS);

void setup() {
  lcd.init();                      
  lcd.backlight();
  lcd.clear();
  Serial.begin(9600);
}

void loop() {
  //leitura da umidade
  int umidade = analogRead(UMIDADE_SOLO_PIN);
  
  //lendo e convertendo a temperatura 
  voltage = getVoltage(temp_pin);
  tempC = ((voltage - 0.5) * 100);
  
  // escrevendo umidade e temperatura no lcd
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Umidade: ");
  lcd.print(umidade);
  lcd.setCursor(0,1);
  lcd.print("Temperatura:");
  lcd.print(tempC);
  
  delay(1000);
}

// função que calcula a voltagem 
float getVoltage(int pin){
	return(analogRead(pin) * 0.004882814);
}
