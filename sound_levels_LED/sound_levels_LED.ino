Measuring sound levels in a sample window of 50ms (T = 50ms => f = 20Hz)
and lighting LEDs according to these levels.
Humans hear frequencies from 20Hz up to 20kHz (although the upper limit varies 
for different people.
*/

const int sample_window = 50; // this is the size of the sample window in ms
unsigned int sample; // stores the level of a measured sample

/*
The LEDs are connected as follows: 
- the green LED to pin 6
- the yellow LED to pin 5
- the red LED to pin 3
*/
int G_led = 6;
int Y_led = 5;
int R_led = 3;


void setup()
{
    Serial.begin(9600);
    pinMode(G_led, OUTPUT);
    pinMode(Y_led, OUTPUT);
    pinMode(R_led, OUTPUT);
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
    vpp = (peak_to_peak * 3.3) / 1023;
    
    Serial.println(vpp);
    
    if (vpp < 1) {
        light_LED(G_led);
    } else if ((vpp > 1) && (vpp < 1.8)) {
        light_LED(Y_led);
    } else if (vpp > 1.8) {
        light_LED(R_led);
    }
}

void light_LED (int LED)
{
    digitalWrite(LED, HIGH);
    delay(150);
    digitalWrite(LED, LOW);
}
