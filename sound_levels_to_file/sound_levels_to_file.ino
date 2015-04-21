#include <SD.h>
/* 
Measuring sound levels in a sample window of 50ms (T = 50ms => f = 20Hz)
Humans hear frequencies from 20Hz up to 20kHz (although the upper limit varies 
for different people.
*/

const int sample_window = 10; // this is the size of the sample window in ms
unsigned int sample; // stores the level of a measured sample
File my_file;

void setup()
{
    Serial.begin(9600);
    pinMode(10, OUTPUT);
    
    if (!SD.begin(4)) {
      Serial.println("initialization failed!");
      return;
    }
    Serial.println("initialization done.");
}

void loop()
{
    // millis() is a function that returns the number of milliseconds since the program
    // started, as an unsigned long
    unsigned long loop_start = millis();
    unsigned int peak_to_peak = 0; // peak to peak level
    double vpp = 0; // peak to peak voltage
    unsigned int max_level = 512;
    unsigned int min_level = 512;

    while (millis() - loop_start < sample_window) {
        sample = analogRead(0); // the microphone is connected to Arduino's Analog Input pin no. 0
        if (sample > max_level) {
            max_level = sample;
        } else if (sample < min_level) {
            min_level = sample;
        }
    }
    
    peak_to_peak = max_level - min_level;
    // The microphone's Vcc is connected to Arduino's 3.3V. If you choose to connect it to 5V
    // remember to also change the value below, for a correct conversion. 
    Serial.println(peak_to_peak);
    my_file = SD.open("rain10ms.txt", FILE_WRITE);
    if (my_file) {
        my_file.println(peak_to_peak);
        my_file.close();
    } else {
        Serial.println("error opening file");
    }
}

