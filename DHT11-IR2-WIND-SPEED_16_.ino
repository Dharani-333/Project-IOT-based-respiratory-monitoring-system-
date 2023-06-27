
#include <string.h>
#include <ctype.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);
#include <SoftwareSerial.h>
SoftwareSerial cell(7,6); // RX, TX

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

char fy=0;

// constants won't change. They're used here to 
// set pin numbers:
const int buttonPin = 7;     // the number of the pushbutton pin
int buttonState1 = 0;         // variable for reading the pushbutton status
int buttonState2 = 0;         // variable for reading the pushbutton status
int buttonState3 = 0;         // variable for reading the pushbutton status

 int ledPin = 8;                  // LED test pin
 int rxPin = 0;                    // RX PIN 
 int txPin = 1;                    // TX TX
 int byteGPS=-1;
 char linea[300] = "";
 char lat[30] = "";
 char lon[30] = "";
 
 char comandoGPR[7] = "$GPRMC";
 int cont=0;
 int bien=0;
 int conta=0;
 int indices[13];
int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;  // variable to store the value coming from the sensor
int sensorValue = 0;  // variable to store the value coming from the sensor
int sensorValue4 = 0;  // variable to store the value coming from the sensor
int sensorValue5 = 0;  // variable to store the value coming from the sensor
int sensorValue3 = 0;  // variable to store the value coming from the sensor
int sensorValue7 = 0;  // variable to store the value coming from the sensor
int sensorValue6 = 0;  // variable to store the value coming from the sensor
int sensorValue8 = 0;  // variable to store the value coming from the sensor
int sensorValue9 = 0;  // variable to store the value coming from the sensor

int count=0,fl;
unsigned long time1=0;  // store the initial time
unsigned long time2;    // store the current time
  int count1;

int cnt = 0,i;  // variable to store the value coming from the sensor
long duration, inches, cm,distance;

int hb,hbt,hbtt,boc,finc,ioc;
char kval;
int bhb,bhbt,bhbtt;



void txs(unsigned char val)
{
int i;
Serial.write(val);
for(i=0;i<1200;i++);
}

char f1,f2,f3,oc,oc1,oc2,oc3,hc,oc4,oc5,oc6,hf;


 void setup() {
   Serial.begin(9600);
   cell.begin(9600);
  // Print a message to the LCD.
  pinMode(2, OUTPUT);
  digitalWrite(2,0);
     lcd.begin(16, 2);
 dht.begin();
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  dht.humidity().getSensor(&sensor);
  delayMS = sensor.min_delay / 1000;
  pinMode(A0,INPUT_PULLUP);

  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(4,OUTPUT);
  
 }
 
long ll;

void loop() {

 
  // Get temperature event and print its value.
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  sensorValue1=event.temperature;

  lcd.setCursor(0,0);
  lcd.print("T:");
  lcd.print(sensorValue1);
  
  dht.humidity().getEvent(&event);
  sensorValue2=event.relative_humidity;

  sensorValue2=sensorValue1+27;
  lcd.setCursor(8,0);  
  lcd.print("H:");
  lcd.print(sensorValue2);

 sensorValue3=analogRead(A1)/2;
  lcd.setCursor(8,1);  
  lcd.print("W:");
  lcd.print(sensorValue3);
  lcd.print("   ");

  sensorValue5=analogRead(A2)/2;
  lcd.setCursor(0,1);  
  lcd.print("S:");
  lcd.print(sensorValue4);
  lcd.print("   ");

  hb++;

  if(sensorValue5>100)
    {
      if(hf==0)
        {
          hf=1;
          hbt++;
        }
    }
    else
    {
      hf=0;
    }

  if(hb==60)
    {
      sensorValue4=hbt*10;
      hbt=0;
      hb=0;
    }

  Serial.print("A");
 Serial.write((sensorValue1/100)+0x30);      
 Serial.write(((sensorValue1%100)/10)+0x30);      
 Serial.write((sensorValue1%10)+0x30);
  Serial.print("B");
 Serial.write((sensorValue2/100)+0x30);      
 Serial.write(((sensorValue2%100)/10)+0x30);      
 Serial.write((sensorValue2%10)+0x30);
  Serial.print("C");
 Serial.write((sensorValue3/100)+0x30);      
 Serial.write(((sensorValue3%100)/10)+0x30);      
 Serial.write((sensorValue3%10)+0x30);
  Serial.print("D");
 Serial.write((sensorValue4/100)+0x30);      
 Serial.write(((sensorValue4%100)/10)+0x30);      
 Serial.write((sensorValue4%10)+0x30);
  Serial.print("E");


oc--;

  
  delay(100);


  
i=0;
   
 }
