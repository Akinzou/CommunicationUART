#include <Arduino.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h> 
#include <IRremote.h>
#include <SPI.h>
#include <SD.h>
#include <Wire.h>

int RECV_PIN = B1;
OneWire oneWire(B0);
DallasTemperature sensors(&oneWire);
LiquidCrystal lcd(A0, A1, A2, A3, A4, A5);
IRrecv irrecv(RECV_PIN);
decode_results results;
int mode = 0x800FF422;
int pin_Startowy = 10;
File myFile;

void setup(void) {
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Akt. temp:"); 
  sensors.begin();
  lcd.setCursor(0, 1);
  irrecv.enableIRIn();

  
  for(int i = pin_Startowy; i<(pin_Startowy*2); i++)
  {
     pinMode(i, OUTPUT);
     digitalWrite(i, HIGH);
  }

}

void zapal(int x)
{
    for(int i = 0; i<9; i++)
  {
    digitalWrite((pin_Startowy+i), HIGH);
  }
  for(int i = 0; i<x; i++)
  {
    digitalWrite((pin_Startowy+i), LOW);
  }
}
 
void loop(void) { 
  
  sensors.requestTemperatures();
  float temperatura = sensors.getTempCByIndex(0);
  lcd.setCursor(0, 1);
  switch(mode)
  {
    case 0x800FF422:
      lcd.print(temperatura); 
      Serial.println("Cel");
      lcd.setCursor(5, 1);
      lcd.print("*C");
      break;

    case 0x800F7422:
      lcd.print(temperatura * 1.8 + 32); 
      lcd.setCursor(5, 1);
      Serial.println("Fahren");
      lcd.print(" F");
      break;
  }
  
  if (irrecv.decode(&results))
  {
    mode = results.value;
    irrecv.resume();
  }

  if(Serial.available() > 0)
  {
    if(Serial.read() == 's')
    {
      switch(mode)
      {
        
        case 0x800FF422:
          mode = 0x800F7422;
          break;
    
        case 0x800F7422:
          mode = 0x800FF422;
          break;
          
      }
    }

  }  

  if(temperatura >= 5)
  {
    zapal(1);
  }

  if(temperatura >= 10)
  {
    zapal(2);
  }

  if(temperatura >= 15)
  {
    zapal(3);
  }

  if(temperatura >= 20)
  {
    zapal(4);
  }

  if(temperatura >= 20)
  {
    zapal(4);
  }

    if(temperatura >= 25)
  {
    zapal(5);
  }

    if(temperatura >= 30)
  {
    zapal(6);
  }

    if(temperatura >= 35)
  {
    zapal(7);
  }

      if(temperatura >= 40)
  {
    zapal(8);
  }

  delay(280);

}
