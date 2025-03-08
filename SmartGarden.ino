//www.elegoo.com
//2016.12.9

/*
  LiquidCrystal Library - Hello World

 Demonstrates the use a 16x2 LCD display.  The LiquidCrystal
 library works with all LCD displays that are compatible with the
 Hitachi HD44780 driver. There are many of them out there, and you
 can usually tell them by the 16-pin interface.

 This sketch prints "Hello World!" to the LCD
 and shows the time.

  The circuit:
 * LCD RS pin to digital pin 7
 * LCD Enable pin to digital pin 8
 * LCD D4 pin to digital pin 9
 * LCD D5 pin to digital pin 10
 * LCD D6 pin to digital pin 11
 * LCD D7 pin to digital pin 12
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)

 Library originally added 18 Apr 2008
 by David A. Mellis
 library modified 5 Jul 2009
 by Limor Fried (http://www.ladyada.net)
 example added 9 Jul 2009
 by Tom Igoe
 modified 22 Nov 2010
 by Tom Igoe

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/LiquidCrystal
 */

// include the library code:

#include<Servo.h>
#include <LiquidCrystal.h>
#include <dht11.h>
dht11 DHT;
#define DHT11_PIN 4
#define LED_VERDE A0
#define LED_GIALLO A1
#define LED_ROSSO A3
#define FOTORESISTENZA A14
#define LUCE A7
#define PIRSENSOR 2
#define LUCEINTERNA A8
#define ENABLE_FAN 6
#define SOIL_SENSOR A11
#define RELE_SERVO 25
//#define RELE 24
//#define WATER_LEVEL A5
int low=1023;
int high=0;
int sensor;
bool detected=false;

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

byte termometro[8] = //icon for termometer
{
  B00100,
  B01010,
  B01010,
  B01110,
  B01110,
  B11111,
  B11111,
  B01110
};


byte umidita[8] = //icon for water droplet
{
  B00100,
  B00100,
  B01010,
  B01010,
  B10001,
  B10001,
  B10001,
  B01110,
};

  const int DRY_SOIL=503;
  const int WET_SOIL=218;
  bool stat1=true;
  bool stat2=false;
  Servo servoMotor;
  
void setup() {
  
  // set up the LCD's number of columns and rows:
  servoMotor.attach(RELE_SERVO);
  servoMotor.write(180);
  lcd.begin(16, 2);
  Serial.begin(9600);
  pinMode(PIRSENSOR,INPUT);
  pinMode(SOIL_SENSOR,INPUT);
  pinMode(DHT11_PIN,INPUT);
  pinMode(ENABLE_FAN,OUTPUT);
  //pinMode(RELE,OUTPUT);
  //digitalWrite(RELE,HIGH);
  analogWrite(LUCEINTERNA,0);
  attachInterrupt(digitalPinToInterrupt(PIRSENSOR), motion, CHANGE);
  lcd.print("Calibrating...");
  while(millis()<4000)
  {
    //millis ritorna i millisecondi dall'accensione
    sensor=analogRead(FOTORESISTENZA);
    
    if(sensor<low)
      low=sensor;
    if(sensor>high)
      high=sensor;
  }
  lcd.clear();
  lcd.print("Calibration done...");
  
  lcd.clear();
  lcd.print("SMART GARDEN");
  lcd.createChar(1, termometro);
  lcd.createChar(2, umidita);
  
}

void motion()
{
  detected=!detected;
  if(detected)
  {
    analogWrite(LUCEINTERNA,255);
  }
  else
  {
    analogWrite(LUCEINTERNA,0);
  }
  
  
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  //lcd.print(millis() / 1000);

  int chk;
  chk = DHT.read(DHT11_PIN);    // READ DATA
   // DISPLAT DATA
  lcd.write(2);
  lcd.print(" ");
  lcd.print(DHT.humidity,1);
  lcd.print("%");
  lcd.print("    ");
  lcd.write(1);
  lcd.print((char)223);
  lcd.print(DHT.temperature,1);
  lcd.print("C");

  
  if(DHT.temperature<=30)
  {
  analogWrite(LED_VERDE,255);
  analogWrite(LED_ROSSO,0);
  analogWrite(LED_GIALLO,0);
  analogWrite(ENABLE_FAN,0); 
 
  }
  if(DHT.temperature>30 && DHT.temperature<50)
  {
  analogWrite(LED_VERDE,0);
  analogWrite(LED_GIALLO,255);
  analogWrite(LED_ROSSO,0);
  analogWrite(ENABLE_FAN,180); 
 
  }
  if(DHT.temperature>=50)
  {
  analogWrite(LED_VERDE,0);
  analogWrite(LED_GIALLO,0);
  analogWrite(LED_ROSSO,255);
  analogWrite(ENABLE_FAN,255); 
  }

  sensor=analogRead(FOTORESISTENZA);
 
  if(sensor<=(high+low)/2)
  analogWrite(LUCE,255);
  if(sensor>(high+low)/2)
  analogWrite(LUCE,0);

    int soilSensor=analogRead(SOIL_SENSOR);
    //Serial.println(soil);
    int soilHumidity=map(soilSensor,WET_SOIL,DRY_SOIL,100,0);
    /*Serial.print(soilHumidity);
    Serial.println("%");*/
    

    
    if(soilHumidity<50)
    {
      if(stat1!=stat2)
      {
        servoMotor.write(90);
        stat2=stat1;
      }
    }
    else
    {
    servoMotor.write(180);
    stat2=false;
    }

  


}
