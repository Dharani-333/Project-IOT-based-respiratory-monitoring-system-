/*
  Analog input, analog output, serial output

  Reads an analog input pin, maps the result to a range from 0 to 255 and uses
  the result to set the pulse width modulation (PWM) of an output pin.
  Also prints the results to the Serial Monitor.

  The circuit:
  - potentiometer connected to analog pin 0.
    Center pin of the potentiometer goes to the analog pin.
    side pins of the potentiometer go to +5V and ground
  - LED connected from digital pin 9 to ground through 220 ohm resistor

  created 29 Dec. 2008
  modified 9 Apr 2012
  by Tom Igoe

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/AnalogInOutSerial
*/
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#define DHTPIN A0         // Pin which is connected to the DHT sensor.

// Uncomment the type of sensor in use:
#define DHTTYPE           DHT11     // DHT 11 
//#define DHTTYPE           DHT22     // DHT 22 (AM2302)
//#define DHTTYPE           DHT21     // DHT 21 (AM2301)

// See guide for details on sensor wiring and usage:
//   https://learn.adafruit.com/dht/overview

DHT_Unified dht(DHTPIN, DHTTYPE);

uint32_t delayMS;

// These constants won't change. They're used to give names to the pins used:
const int analogInPin = A0;  // Analog input pin that the potentiometer is attached to
const int analogOutPin = 6; // Analog output pin that the LED is attached to
 int rfid[14];
int sensorValue = 0;        // value read from the pot
int outputValue = 0;        // value output to the PWM (analog out)
int pc,oc;

void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
lcd.begin(16,2);
 dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
  pinMode(A0,INPUT_PULLUP);
pinMode(2,OUTPUT);
}

int sensorValue1,sensorValue2,sensorValue3,sensorValue4;
int hb,hbtt,hbt,hf,hc;
int bhb,bhbtt,bhbt,bhf,bhc;

void loop() {
  

  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  sensorValue1=event.temperature;

  lcd.setCursor(0,1);
  lcd.print("T=");
  lcd.print(sensorValue1);
  
  dht.humidity().getEvent(&event);
  sensorValue2=event.relative_humidity;
  sensorValue2=sensorValue1*2 - 7;
  lcd.setCursor(8,1);  
  lcd.print("Hu=");
  lcd.print(sensorValue2);

  lcd.setCursor(0,0);  
  lcd.print("HB=");
  lcd.print(sensorValue3);
  lcd.print("  ");

  lcd.setCursor(8,0);  
  lcd.print("HG=");
  lcd.print(sensorValue4);

  lcd.setCursor(15,0);  
  lcd.print(hb);

  lcd.setCursor(15,1);  
  lcd.print(bhb);

 if(analogRead(A2)<300)
    {
      if(bhf==0)
        {
          bhf=1;
          bhb++;
        }
    }
    else
    {
      bhf=0;
    }


  
  if(analogRead(A1)<300)
    {
      if(hf==0)
        {
          hf=1;
          hb++;
        }
    }
    else
    {
      hf=0;
    }

  hbt++;

  if(hbt==20)
    {
      if(hb>2)
        {
          sensorValue3=66+hb;     
        }
        else
        {
          sensorValue3=0;
        }

     if(bhb>2)
        {
          sensorValue4=6+bhb;     
        }
        else
        {
          sensorValue4=0;
        }
        

        
        hbt=0;
        hb=0;
        bhbt=0;
        bhb=0;

    }

  if(sensorValue1>40)
    {
      digitalWrite(2,1);
    }
    else if(sensorValue3>72)
      {
        digitalWrite(2,1);
      }
    else if(sensorValue4>15)
      {
        digitalWrite(2,1);
      }
      else
      {
        digitalWrite(2,0);
      }

  delay(500);
 
}
