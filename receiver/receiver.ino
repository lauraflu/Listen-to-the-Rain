#include <Wire.h>
#include <SoftwareSerial.h> 
#include <Arduino.h>
#include <Suli.h>
#include "Seeed_LED_Bar_Arduino.h"
#include "TM1637.h"

#define CLK 7
#define DIO 8
#define MAX 3500
#define SOP '<'
#define EOP '>'

TM1637 disp(CLK,DIO); //D7 & D8 
SeeedLedBar bar(A4, A5); //clock & data of the led bar
SoftwareSerial xbee(2,3); //rx, tx
void light_leds(int);
void digit_display(int);

void setup() 
{
  
  Serial.begin(9600);//Remember that the baud must be the same on both arduinos
  xbee.begin(9600);
  disp.init();
  pinMode(10,OUTPUT);
}

char val;
char str[10];
float power;
int power_i;
bool starts = false;
bool ends = false;
int i = 0;

void loop() {
  
    while (xbee.available()) 
    {
         val = xbee.read();
         if (val == SOP) {
             i = 0;
             str[i] = '\0';
             starts = true;
             ends = false;
         } else if (val == EOP) {
             ends = true;
             break;       
         } else {
             if (i < 10) {
                 str[i] = val;
                 i++;
                 str[i] = '\0';
             }
         }
    }
  
    if (starts && ends) {
        starts = false;
        ends = false;
        i = 0;
        power = atof(str);
        power_i = (int)power;
        light_leds(power_i);
        digit_display(power_i);
        str[i] = '\0';
    }
}

void light_leds(int c)
{
  if (c >= 4600)
      bar.indexBit(0b000001111111111);
  else if (c >= 4200)
      bar.indexBit(0b000001111111110);
  else if (c >= 3800)
      bar.indexBit(0b000001111111100);
  else if (c >= 3400)
      bar.indexBit(0b000001111111000);
  else if (c >= 3000)
      bar.indexBit(0b000001111110000);
  else if (c >= 2600)
      bar.indexBit(0b000001111100000);
  else if (c >= 2200)
      bar.indexBit(0b000001111000000);
  else if (c >= 1800)
      bar.indexBit(0b000001110000000);
  else if (c >= 1400)
      bar.indexBit(0b000001100000000);
  else 
      bar.indexBit(0b000001000000000);  
}

void digit_display (int x)
{
  disp.clearDisplay();
  int pos = 3;  
  while(x != 0)
  {
      int digit = x % 10;
      disp.display(pos, digit);
      pos--;
      x = x / 10;
  }
  delay(200);
}
