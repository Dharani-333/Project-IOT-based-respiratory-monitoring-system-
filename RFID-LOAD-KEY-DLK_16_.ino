
 #include <string.h>
 #include <ctype.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd(13, 12, 11, 10, 9, 8);

#include <SoftwareSerial.h>
SoftwareSerial mySerial(7, 6); // RX, TX

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

 char comandoGPR[7] = "$GPRMC";
 int cont=0;
 int bien=0;
 int conta=0;
 int rfid[14];
 int finger[10];
int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;  // variable to store the value coming from the sensor
int sensorValue3 = 0;  // variable to store the value coming from the sensor
int sensorValue4 = 0;  // variable to store the value coming from the sensor
int sensorValue5 = 0;  // variable to store the value coming from the sensor
int sensorValue6 = 0;  // variable to store the value coming from the sensor
int sensorValue7 = 0;  // variable to store the value coming from the sensor

int cnt = 0,fl=0,i;  // variable to store the value coming from the sensor
long duration, inches, cm,distance;
char fl1,fl2,fl3,fl4;

int am,amt;
void txs(unsigned char val)
{
int i;
Serial.write(val);
for(i=0;i<1200;i++);
}


 void setup() {
  
   Serial.begin(9600);
 mySerial.begin(9600);
 
    lcd.begin(16, 2);
     lcd.print("ORGAN RFID                ");
delay(2000);
    lcd.setCursor(0,1);
       lcd.print("                           ");

pinMode(A5,INPUT_PULLUP);
pinMode(A1,INPUT_PULLUP);
pinMode(A2,INPUT_PULLUP);
pinMode(A3,INPUT_PULLUP);
pinMode(A4,INPUT_PULLUP);
pinMode(2,OUTPUT);
digitalWrite(2,0);
 }


int yc,zc;

int bs,kf;

long ll;

 void loop() {
   //digitalWrite(ledPin, HIGH);
  i=0;
delay(1000);

if (mySerial.available()) {
   
    rfid[0]=mySerial.read();
    rfid[1]=mySerial.read();
    rfid[2]=mySerial.read();
    rfid[3]=mySerial.read();
    rfid[4]=mySerial.read();
    rfid[5]=mySerial.read();
    rfid[6]=mySerial.read();
    rfid[7]=mySerial.read();
    rfid[8]=mySerial.read();
    rfid[9]=mySerial.read();
    rfid[10]=mySerial.read();
    rfid[11]=mySerial.read();
    rfid[12]=mySerial.read();
    rfid[13]=mySerial.read();
    
   if(rfid[11]=='8')
   {
    yc=1;
    lcd.setCursor(0,0);
    lcd.print("Heart      ");
    delay(2000);
   }

   if(rfid[11]=='1')
   {
   yc=2;  
    lcd.setCursor(0,0);
    lcd.print("Kidney      ");
    delay(2000);
   }
   
   if(rfid[11]=='C')
   {
   yc=3;  
    lcd.setCursor(0,0);
    lcd.print("Liver      ");
    delay(2000);
   }

   lcd.setCursor(0, 1);
   lcd.write(rfid[11]);
   lcd.print(yc);
}


  if(yc>0)
    {
        lcd.setCursor(0,0);
        lcd.print("Enter PIN    ");
        while(amt<1000)
          {
              if(digitalRead(A1)==0)
                {
                    amt=(amt*10)+1;  
                    delay(1000);
                }
              if(digitalRead(A2)==0)
                {
                    amt=(amt*10)+2;  
                    delay(1000);
                }
              if(digitalRead(A3)==0)
                {
                    amt=(amt*10)+3;  
                    delay(1000);
                }
              if(digitalRead(A4)==0)
                {
                    amt=(amt*10)+4;  
                    delay(1000);
                }
              if(digitalRead(A5)==0)
                {
                    amt=(amt*10)+5;  
                    delay(1000);
                }

          lcd.setCursor(12,0);
          lcd.print(amt);
          lcd.print("    ");
          }
        if(amt==2341)
          {
            lcd.setCursor(0,0);
            lcd.print("PIN OK OPEN      ");
            delay(1000);
            lcd.setCursor(0,0);
            lcd.print("PLACE ORGAN      ");            
            int yp;
            for(yp=0;yp<20;yp++)
              {
               lcd.setCursor(14,0);
               lcd.print(yp/10);
              delay(500);
                          lcd.setCursor(0,1);
            lcd.print("Wt:");
            sensorValue1=analogRead(A0);
            if(sensorValue1>300)
              sensorValue1=sensorValue1-300;
            else
              sensorValue1=0;
            lcd.print(sensorValue1);
            lcd.print("    ");
            

              }
            while(1)
            {
            lcd.setCursor(0,1);
            lcd.print("Wt:");
            sensorValue1=analogRead(A0);
            if(sensorValue1>300)
              sensorValue1=sensorValue1-300;
            else
              sensorValue1=0;
            lcd.print(sensorValue1);
            lcd.print("    ");
            delay(200);
              if(yc==1)
                {
                  if((sensorValue1<100)&&(sensorValue1>50))
                    {
                        lcd.setCursor(0,0);
                        lcd.print("Heart OK      ");                                  
                        Serial.print("*Heart_Weight_Ok#");                     
                    }
                else
                {
                  digitalWrite(2,1);
                  Serial.print("*Orgran_Weight_Not_Ok#");
                  while(1);                  
                }
                }
               else if(yc==2)
                {
                  if((sensorValue1<150)&&(sensorValue1>100))
                    {
                        lcd.setCursor(0,0);
                        lcd.print("Kidney OK      ");                                  
                        Serial.print("*Kidney_Weight_Ok#");
                        yc=0;
                    }
                else
                {
                  digitalWrite(2,1);
                  Serial.print("*Orgran_Weight_Not_Ok#");
                  while(1);                  
                }

                }            
              else if(yc==3)
                {
                  if((sensorValue1<200)&&(sensorValue1>150))
                    {
                        lcd.setCursor(0,0);
                        lcd.print("Liver OK      ");                                  
                        Serial.print("*Liver_Weight_Ok#");
                        yc=0;
                    }
                else
                {
                  digitalWrite(2,1);
                  Serial.print("*Orgran_Weight_Not_Ok#");
                  while(1);                  
                }

                }  

              }
              while(1);
          }
        else
           {
            lcd.setCursor(0,0);
            lcd.print("PIN NOT OK      ");
             Serial.print("*PIN_Not_Ok#");
            delay(1000);
            yc=0;            
           }
      
    }

    

   
 }
