#include "DHT.h"
#include <SoftwareSerial.h>
SoftwareSerial s(5,6);
#define DHTPIN 2
const int sensor_pin = A0;
const int pingPin = 7;
const int echoPin = 8;
const int motorPin = 4;

#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  s.begin(9600);
  Serial.begin(9600); 
  dht.begin();
}

void loop() {
  float moisture_percentage;
  int sensor_analog;
  delay(1000);

   //Water level using ULTRASONIC SENSOR
   long duration, inches, cm,tank_height_inches=6,tank_height_cm=16;
   pinMode(pingPin, OUTPUT);
   digitalWrite(pingPin, LOW);
   delayMicroseconds(2);
   digitalWrite(pingPin, HIGH);
   delayMicroseconds(10);
   digitalWrite(pingPin, LOW);
   pinMode(echoPin, INPUT);
   duration = pulseIn(echoPin, HIGH);
   inches = tank_height_inches - microsecondsToInches(duration);
   cm = microsecondsToCentimeters(duration);
   cm =  tank_height_cm - cm;
//   inches=microsecondsToInches(duration);
//   cm=microsecondsToCentimeters(duration);
   
   delay(100);

  //Soil mositure using SOIL MOISTURE SENSOR
  sensor_analog = analogRead(sensor_pin);
  //Serial.println(sensor_analog);
  moisture_percentage = ( 100 - ( (sensor_analog/1023.00) * 100 ) );
  delay(100);

  //Temperature, Humidity using DHT11
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  float f = dht.readTemperature(true);
  
  // Check if any reads failed and exit early (to try again)
  if (isnan(h) || isnan(t) || isnan(f)) 
  {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  //Heat index
  float hi = dht.computeHeatIndex(f, h);  // Must send temp in Fahrenheit

  //Water supply activation
  if(moisture_percentage<40 && f>85)
  {
    pinMode(motorPin, OUTPUT);
    digitalWrite(motorPin, HIGH);
  }
  else
  {
    pinMode(motorPin, OUTPUT);
    digitalWrite(motorPin, LOW);
  }

  Serial.print("\nHeat Index : ");
  Serial.print(hi);
  Serial.print("\nHumidity : "); 
  Serial.print(h);
  Serial.print("%\n");
  Serial.print("Moisture Percentage : ");
  Serial.print(moisture_percentage);
  Serial.print("%\n");
  Serial.print("Temperature:");
  Serial.print("\nIn Celcius : ");
  Serial.print(t);
  Serial.print("\nIn Farenheit : ");
  Serial.print(f);
  Serial.print("\nWater level : ");
  Serial.print(inches);
  Serial.print("in, ");
  Serial.print(cm);
  Serial.print("cm");
  
  Serial.println("\n\n");

  if(s.available()>0)
  {
    s.write(int(hi));
    delay(200);
    s.write(int(h));
    delay(200);
    s.write(int(moisture_percentage));
    delay(200);
    s.write(int(t));
    delay(200);
    s.write(int(f));
    delay(200);
    s.write(int(cm));
    delay(200);
  }
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74 / 2;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29 / 2;
}
