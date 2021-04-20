#include <stdlib.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#ifndef STASSID
#define STASSID "SSID Goes Here"
#define STAPSK  "Password goez here"
#endif

const char* ssid = STASSID;
const char* password = STAPSK;


int frame = 0;
int delayTime = 500;



#include <PxMatrix.h>

#include "megu.h"

#ifdef ESP8266

#include <Ticker.h>
Ticker display_ticker;
#define P_LAT 16
#define P_A 5
#define P_B 4
#define P_C 15
#define P_D 12
#define P_E 0
#define P_OE 2

#endif




PxMATRIX display(64,32,P_LAT, P_OE,P_A,P_B,P_C,P_D);

void display_updater()
{
  display.display(70);
}





const char* restoreAddress = "192.168.2.1";






uint16_t hues [] = {0x5fff, 0xfabf, 0xfff4, 0x5ff2};
int hueCount = 0;


int beatLength = 163;

char beatString[] = "x..xx...x...x...x..xx...x...x...x..xx...x...x...x..xx...x...xxxxx..xx...x...x...x..xx...x...x...x..xx...x...x...x...x...x...xxxx";
int beat = 0;





void setup() {
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println("Connection Failed! Rebooting...");
    delay(5000);
    ESP.restart();
  }


  // Hostname defaults to esp8266-[ChipID]
   ArduinoOTA.setHostname("LED1");

  // No authentication by default
 //ArduinoOTA.setPassword("SkySky");


  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else { // U_FS
      type = "filesystem";
    }

    // NOTE: if updating FS this would be the place to unmount FS using FS.end()
    Serial.println("Start updating " + type);
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) {
      Serial.println("Auth Failed");
    } else if (error == OTA_BEGIN_ERROR) {
      Serial.println("Begin Failed");
    } else if (error == OTA_CONNECT_ERROR) {
      Serial.println("Connect Failed");
    } else if (error == OTA_RECEIVE_ERROR) {
      Serial.println("Receive Failed");
    } else if (error == OTA_END_ERROR) {
      Serial.println("End Failed");
    }
  });
  ArduinoOTA.begin();
  Serial.println("Ready");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());




  display.begin(16);
  display.flushDisplay();
  //display.setTextColor(myCYAN);
  display.setCursor(2,0);
  //display.print("Pixel");

   #ifdef ESP8266
    display_ticker.attach(0.004, display_updater);
  #endif

//  delay(1000);

\
  display.clearDisplay();
  display.setCursor(0,0);

 delay(1000);
 ArduinoOTA.handle();
  delay(1000);
 ArduinoOTA.handle();
 delay(1000);
 ArduinoOTA.handle();
  delay(1000);
 ArduinoOTA.handle();



  originalPrintMegu();
  
  
}

void restoreDisplay(){
  WiFiClient client;
  if (client.connect(restoreAddress, 8000))
  {
    client.print(String("GET /") + " HTTP/1.1\r\n" +
                 "Host: " + restoreAddress + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );

   while (client.connected() || client.available())
    {
      if (client.available())
      {
        String incomingPixel = client.readStringUntil('\n');
        int16_t int16Pixel = strtol(incomingPixel.c_str(), NULL, 0);
        display.drawPixel(0, 0, int16Pixel);
      }
    }
    client.stop();
    
  }
  
}




void originalPrintMegu(){
  for (int y = 0; y < 32; y++){
    for (int x = 0; x < 64; x++){
       display.drawPixel(x, y,  megu[((64*y)+x)]);
       delay(2);
    }
  }
   ArduinoOTA.handle();
}


void colourPrintMegu(){
  for (int y = 0; y < 32; y++){
    for (int x = 0; x < 64; x++){
      if (megu[((64*y)+x)] == 0xFFFF){
        display.drawPixel(x, y, hues[hueCount]);
      } else{
        display.drawPixel(x, y, 0x0000);
      }
       //ArduinoOTA.handle();
    }
  }
  if(hueCount == 3) {
    hueCount = 0;
  } else {
    hueCount++;
  }
}

void loop() {
 //restoreDisplay();


  if ((beatString[beat]) == 'x') {
    colourPrintMegu();
  }
 delay(beatLength);
 if (beat == 127) {
  beat = 0;
 } else {
  beat++;
 }
 ArduinoOTA.handle();
 

}
