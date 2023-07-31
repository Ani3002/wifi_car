#define ENA   14                  GPIO14(D5)
#define ENB   12                  GPIO12(D6)
#define IN_1  15                  GPIO15(D8)
#define IN_2  13                  GPIO13(D7)
#define IN_3  2                   GPIO2(D4)
#define IN_4  0                   GPIO0(D3)
#define MD    10           // Metal detector
#define ledPin 5
#define ledPin1 4
#include <ESP8266WiFi.h>
#include <WiFiClient.h> 
#include <ESP8266WiFiMulti.h>
#include <ESP8266WebServer.h>
#include <ESP8266HTTPClient.h>



String command;             //String to store app command state.
int speedCar = 800;         // 400 - 1023.
int speed_Coeff = 3;
String MDStatee = "H";
int MDState = 0;
unsigned long previousMillis2 = 0;
const long intervalOnOff2 = 200; // LED ON/OFF duration in milliseconds
const long intervalOff2 = 500; // LED OFF duration in milliseconds
int blinkCount2 = 0;
int ledState = LOW;
int ledState1 = LOW;



const char* ssid = "Car";
const char *password = "AmitabhaRouth";
ESP8266WebServer server(80);
// AsyncWebServer server(80);


void setup() 
{
 pinMode(ENA, OUTPUT);
 pinMode(ENB, OUTPUT);  
 pinMode(IN_1, OUTPUT);
 pinMode(IN_2, OUTPUT);
 pinMode(IN_3, OUTPUT);
 pinMode(IN_4, OUTPUT);
 pinMode(MD, INPUT); 
 pinMode(ledPin, OUTPUT);
 pinMode(ledPin1, OUTPUT);

 Serial.begin(115200);
  
// Connecting WiFi

  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
 
  // Starting WEB-server 
  server.on ( "/", HTTP_handleRoot );
  server.onNotFound ( HTTP_handleRoot );

  server.begin();    
}

void goAhead(){ 

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
      //Serial.println(speedCar);
  }

void goBack(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
      //Serial.println(speedCar);
  }

void goRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
      //Serial.println(speedCar);
  }

void goLeft(){

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
      //Serial.println(speedCar);
  }

void goAheadRight(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar/speed_Coeff);
 
      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar);
   }

void goAheadLeft(){
      
      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, HIGH);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, HIGH);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void goBackRight(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar/speed_Coeff);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
  }

void goBackLeft(){ 

      digitalWrite(IN_1, HIGH);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, HIGH);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar/speed_Coeff);
  }

void stopRobot(){  

      digitalWrite(IN_1, LOW);
      digitalWrite(IN_2, LOW);
      analogWrite(ENA, speedCar);

      digitalWrite(IN_3, LOW);
      digitalWrite(IN_4, LOW);
      analogWrite(ENB, speedCar);
 }

void loop() 
{

  server.handleClient(); 
  command = server.arg("State");
  if (command == "F") goAhead();  //
  else if (command == "F1")
  {
    speedCar = 100;
    goAhead();
  }
  else if (command == "F2")
  {
    speedCar = 1023;
    goAhead();
  }
  else if (command == "B") goBack();  //
  else if (command == "B1")
  {
    speedCar = 100;
    goBack();
  }
  else if (command == "B2")
  {
    speedCar = 1023;
    goBack();
  }
  else if (command == "L") goLeft();
  else if (command == "L1")
  {
    speedCar = 170;
    goLeft();
  }
  else if (command == "L2")
  {
    speedCar = 1023;
    goLeft();
  }
  
  else if (command == "R") goRight();
  else if (command == "R1")
  {
    speedCar = 170;
    goRight();
  }
  else if (command == "R2")
  {
    speedCar = 1023;
    goRight();
  }
  else if (command == "I") goAheadRight();
  else if (command == "G") goAheadLeft();
  else if (command == "J") goBackRight();
  else if (command == "H") goBackLeft();
  else if (command == "0") speedCar = 400;
  else if (command == "1") speedCar = 470;
  else if (command == "2") speedCar = 540;
  else if (command == "3") speedCar = 610;
  else if (command == "4") speedCar = 680;
  else if (command == "5") speedCar = 750;
  else if (command == "6") speedCar = 820;
  else if (command == "7") speedCar = 890;
  else if (command == "8") speedCar = 960;
  else if (command == "9") speedCar = 1023;
  else if (command == "S") stopRobot();





  unsigned long currentMillis = millis();
  // Blink pattern logic
  if (blinkCount2 < 3) 
  {
    // LED is currently off, and it's time to turn it on
    if (ledState == LOW && currentMillis - previousMillis2 >= intervalOnOff2) 
    {
      ledState = HIGH;
      ledState1 = HIGH;
      digitalWrite(ledPin, HIGH);
      digitalWrite(ledPin1, HIGH);
      previousMillis2 = currentMillis;
    }
    // LED is currently on, and it's time to turn it off
    else if (ledState == HIGH && currentMillis - previousMillis2 >= intervalOnOff2) 
    {
      ledState = LOW;
      ledState1 = LOW;
      digitalWrite(ledPin, LOW);
      digitalWrite(ledPin1, LOW);
      previousMillis2 = currentMillis;
      blinkCount2++;
    }
  } 
  else 
  {
    // Wait for the longer OFF duration after three blinks
    if (currentMillis - previousMillis2 >= intervalOff2) 
    {
      // Reset blinkCount and restart the blinking pattern
      blinkCount2 = 0;
    }
  }
  //Serial.println("blink2 running");



















}

void HTTP_handleRoot(void) 
{
  if( server.hasArg("State") )
  {
    //server.arg("State"));
  }
  
  
  MDState = digitalRead(MD);
  if (MDState == LOW)
  {
    MDStatee = "L";
  }
  else
  {
    MDStatee = "H";
  }

  server.send ( 200, "text/html",MDStatee);
  //Serial.println("HandleRoot running");
  //delay(1);
}

