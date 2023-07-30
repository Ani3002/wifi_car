#include <Arduino.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <HTTPClient.h>
#include <WiFiClient.h>


#define X_AXIS_PIN 34
#define Y_AXIS_PIN 35
#define SWITCH_PIN 23
#define MD1 22 
#define buttonPin 4
#define ledPin 2


int xAxisValue;
int yAxisValue;
int buttonPushCounter = 0;  // counter for the number of button presses
int buttonState = 0;        // current state of the button
int lastButtonState = 0;    // previous state of the button
int ledState = LOW;             // ledState used to set the LED
unsigned long previousMillis1 = 0;        // will store last time LED was updated
const long intervalOn1 = 200; // LED ON duration in milliseconds
const long intervalOff1 = 2000; // LED OFF duration in milliseconds
unsigned long previousMillis2 = 0;
const long intervalOnOff2 = 200; // LED ON/OFF duration in milliseconds
const long intervalOff2 = 2000; // LED OFF duration in milliseconds
int blinkCount2 = 0;

WiFiMulti WiFiMulti;
String mainURL = "http://192.168.4.1/?State=";
String State = "S";

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("Car", "AmitabhaRouth");
  pinMode(MD1, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  pinMode(buttonPin, INPUT);
  pinMode(ledPin, OUTPUT);
}

void loop() {
  if (WiFiMulti.run() == WL_CONNECTED) 
  {
    WiFiClient client;
    HTTPClient http;
    {
      xAxisValue = analogRead(X_AXIS_PIN);
      yAxisValue = analogRead(Y_AXIS_PIN);  
      
      //Implementing buttonPressCounter
      buttonState = digitalRead(buttonPin);
      if (buttonState != lastButtonState)
      {
        if (buttonState == HIGH) 
        {
          buttonPushCounter++;
        }
        delay(50);   //delay for button rebounce
        //Serial.println("BC counter running");
      }
      lastButtonState = buttonState;
      
      if (buttonPushCounter == 1)
      {
        unsigned long currentMillis = millis();

        if (ledState == LOW && currentMillis - previousMillis1 >= intervalOff1) 
        {
          // LED is currently off, and it's time to turn it on
          ledState = HIGH;
          digitalWrite(ledPin, HIGH);
          previousMillis1 = currentMillis;
        } 
        else if (ledState == HIGH && currentMillis - previousMillis1 >= intervalOn1) 
        {
          // LED is currently on, and it's time to turn it off
          ledState = LOW;
          digitalWrite(ledPin, LOW);
          previousMillis1 = currentMillis;
        }
        //Serial.println("blink1 running");
      }
      else if (buttonPushCounter == 2)
      {
        unsigned long currentMillis = millis();
        // Blink pattern logic
        if (blinkCount2 < 2) 
        {
          // LED is currently off, and it's time to turn it on
          if (ledState == false && currentMillis - previousMillis2 >= intervalOnOff2) 
          {
            ledState = true;
            digitalWrite(ledPin, HIGH);
            previousMillis2 = currentMillis;
          }
          // LED is currently on, and it's time to turn it off
          else if (ledState == true && currentMillis - previousMillis2 >= intervalOnOff2) 
          {
            ledState = false;
            digitalWrite(ledPin, LOW);
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
      else if (buttonPushCounter % 3 == 0) 
      {
        buttonPushCounter = 0;
      }

      
      //Serial.println(buttonPushCounter);
      //Gear 1
      if (buttonPushCounter == 1)
      {
        if (yAxisValue >2100 && yAxisValue<2500 && xAxisValue >2100 && xAxisValue<2500)
        {
          State = "S";
        }
        if (xAxisValue <= 2100)
        {
          State = "L1";
        }
        if (xAxisValue >= 2500)
        {
          State = "R1";
        }
        if (yAxisValue <= 2100)
        {
          State = "F1";
        }
        if (yAxisValue >= 2500)
        {
          State = "B1";
        }
        //Serial.println("gear1 running");
      }

      //Gear 2
      else if (buttonPushCounter == 2)
      {
        if (yAxisValue >2100 && yAxisValue<2500 && xAxisValue >2100 && xAxisValue<2500)
        {
          State = "S";
        }
        if (xAxisValue <= 2100)
        {
          State = "L2";
        }
        if (xAxisValue >= 2500)
        {
          State = "R2";
        }
        if (yAxisValue <= 2100)
        {
          State = "F2";
        }
        if (yAxisValue >= 2500)
        {
          State = "B2";
        }
        //Serial.println("gear2 running");
      }
        
      // Make HTTP request with updated State
      http.begin(client, mainURL + State);
      
      //Serial.println(State);
      // Serial.print("X : ");
      // Serial.print(xAxisValue, DEC);
      // Serial.print(" / Y : ");
      // Serial.println(yAxisValue, DEC);

      int httpResponseCode = http.GET();
      if (httpResponseCode == 200) 
      {
        String response = http.getString();
        Serial.println(response);
        // Process the response further as needed
        if(response == "H")
        {
            digitalWrite(MD1,HIGH);
        }

        else
        {
            digitalWrite(MD1,LOW);
        }
      } 
      // else 
      // {
      //  Serial.print("Error code: ");
      //  Serial.println(httpResponseCode);
      // }   
      //Serial.println("Running");
      http.end();
      
      //delay(1); // Delay between each State interchange
    }
  }
  //Serial.println("loop running");
  //delay(1);
}