#include "DHT.h"
#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <SoftwareSerial.h>
SoftwareSerial s(D1,D0);
int data;
int i=0;

#define FIREBASE_HOST "blitzkrieg-afd58.firebaseio.com" 
#define FIREBASE_AUTH "Kxe1mfJlZVT2pFdt5Oj2oCiHvciOzjrxEOA9OkFS" 
#define WIFI_SSID "Vishnu" 
#define WIFI_PASSWORD "2444666668888888" 

void setup() 
{
  s.begin(9600);
  Serial.begin(9600);
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);
  while (WiFi.status() != WL_CONNECTED) 
  {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());                                                      //print local IP address
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);                                       // connect to firebase
}

void loop() 
{
  s.write("s");
  if (s.available()>0)
  {
    data = s.read();
    if(i%6==0)
    {
      Serial.print("\n\nHeat Index: ");
      Serial.print(data);
      Firebase.pushInt("/Data/1_Heat Index", data);
    }
    else if(i%6==1)
    {
      Serial.print("\nHumidity: "); 
      Serial.print(data);
      Firebase.pushInt("/Data/2_Humidity", data);
    }
    else if(i%6==2)
    {
      Serial.print("\nMoisture Percentage = ");
      Serial.print(data);
      Firebase.pushInt("/Data/3_Moisture level", data);
    }
    else if(i%6==3)
    {
       Serial.print("\nIn Celcius : ");
       Serial.print(data);
       Firebase.pushInt("/Data/4_Tempreature C", data);
    }
    else if(i%6==4)
    {
      Serial.print("\nIn Farenheit : ");
      Serial.print(data);
      Firebase.pushInt("/Data/5_Temperature F", data);
    }
    else if(i%6==5)
    {
      Serial.print("\nWater level: ");
      Serial.print(data);
      Serial.print("cm");
      Firebase.pushInt("/Data/6_Water Level", data);
    }
    i++;    
  }
}
