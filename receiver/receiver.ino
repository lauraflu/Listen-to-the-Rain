#include <SoftwareSerial.h>
#define SOP '<'
#define EOP '>'
SoftwareSerial xbee(2,3); //rx, tx

void setup() 
{
  
  Serial.begin(9600);//Remember that the baud must be the same on both arduinos
  xbee.begin(9600);
  pinMode(10,OUTPUT);
}

char val;
char str[10];
float power;
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
        str[i] = '\0';
        Serial.println(power);
    }
}
