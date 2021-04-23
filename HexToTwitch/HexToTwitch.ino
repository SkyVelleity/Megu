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

//Also, as of now, I'm not sure if it's an issue with my display, but
//it only seems to clearly display Primary, Secondary, and Tertiary colours.
//Anything htat's a mix of R, G, and B tends to wash out into white.
//I'll see if I can fix this up when I have a second panel to test with.




#include "example.h" // 7x7
//#include "Cube.h" // 7x7
//#include "Yuki.h" //16x16



//int lengthOfX = 16; //Not needed, as it's defined in our array header file.
//int lengthOfY = 23; 
int lengthOfZ = 4;


//Set this to the top right corner of your draw location, -32 and -16 will be top right.
//There's a nice gooma now, so I'll set it to centre far left
int startX = -32;    
int startY = 0;

//TODO: Adding in stamping later, will not draw 0xFFFF pixels
bool stamp = false;


String startcode = "!draw";
String quote = "\"";
String inout = ", ";
void setup() {
  Serial.begin(115200);
  delay(500);
  yield();
  delay(500);
}

void loop() {
  delay(100);
  Serial.println("STarto!");
  delay(100);
  Serial.print(quote);
  
  for (int pixelY = 0; pixelY < lengthOfY; pixelY++){
    for (int pixelX = 0; pixelX < lengthOfX; pixelX++){
        byte pixelBHex = arrayName[(  (pixelY * (lengthOfX * lengthOfZ))  +   (pixelX * lengthOfZ)            )];
        byte pixelGHex = arrayName[(  (pixelY * (lengthOfX * lengthOfZ))  +   (pixelX * lengthOfZ)   +  1     )];
        byte pixelRHex = arrayName[(  (pixelY * (lengthOfX * lengthOfZ))  +   (pixelX * lengthOfZ)   +  2     )];
      //  byte pixelAHex = arrayName[(  (pixelY * (lengthOfX * lengthOfZ))  +   (pixelX * lengthOfZ)   +  3     )];
      String printMe = quote + startcode + ' ' + String(startX + pixelX) + ' ' + String(startY + pixelY) + ' ' + String(pixelRHex) + ' ' + String(pixelGHex) + ' ' + String(pixelBHex) + quote;
   
  //    String printMe = quote + startcode + ' ' + String(startX + pixelX) + ' ' + String(startY + pixelY) + ' ' + "0" + ' ' + "0" + ' ' + "0" + quote;

      Serial.print(printMe);
      //Serial.println("Position:");
      Serial.print(inout);
      //Serial.println(String(startX + pixelX) + ' ' + String(startY + pixelY));
      yield();
    }
    Serial.println();
  }
  Serial.print(quote);
  Serial.println("Complete!");
  
 while (true){
  delay (4000);
  }
}
