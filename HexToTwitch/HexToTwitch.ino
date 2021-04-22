//Converts an image created using this:
//https://lvgl.io/tools/imageconverter
//To something you can spam in twitch 
//Give it your image res in arrayX/arrayY, and the co-ordinates you want for your
//top right corner

//I reccomend using
//https://www.pixilart.com/draw#
//-to make art, but literally any image fed into the above converter will work.
//For now, max you can prrobably do is a 64x32 image, if you set
//int startX = -32;
//int startY = -16

#include "Cube.h"

int arrayX = 7;
int arrayY = 7;

int startX = -3;
int startY = 9;

String startcode = "!draw";
void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(100);
  Serial.println("STarto!");
  delay(100);
  for (int pixelY = 0; pixelY < arrayY; pixelY++){
    for (int pixelX = 0; pixelX < arrayX; pixelX++){
      byte pixelBHex = cube[ ((pixelY * 4 * arrayY) +(pixelX * 4))];
      byte pixelGHex = cube[ ((pixelY * 4 * arrayY) +((pixelX * 4) + 1))];
      byte pixelRHex = cube[ ((pixelY * 4 * arrayY) +((pixelX * 4) + 2))];
      String printMe = startcode + ' ' + String(startX + pixelX) + ' ' + String(startY + pixelY) + ' ' + String(pixelRHex) + ' ' + String(pixelGHex) + ' ' + String(pixelBHex);
      Serial.println(printMe);
    }
  }
  
 while (true){
  delay (4000);
  }
}
