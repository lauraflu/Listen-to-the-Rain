const int sample_window = 50; // this is the size of the sample window in ms
const int no_samples = 150; // after 150 received samples, we compress & send them
float power[150];
float sample; // stores the level of a measured sample
float sample_power = 0;

void setup()
{
    Serial.begin(9600);
}

void loop()
{
    // millis() is a function that returns the number of milliseconds since the program
    // started, as an unsigned long
    delay(5000);
    unsigned int cnt_sample = 0; // iterates through the vector
    unsigned int cnt_mean = 1; // for calculating the mean power

    if (cnt_sample < no_samples) {
        unsigned long loop_start = millis();
        Serial.println("loopstart: ");
        Serial.println(loop_start);
        while (millis() - loop_start < sample_window) {
            Serial.println(millis());
            sample = analogRead(0); // the mic is connected to Arduino's Analog Input pin no. 0
            // Serial.println(sample);
            sample = ((sample - 512) * 5) / 1023; // value in volts
            sample_power = sample_power + (sample * sample);
            
            // Serial.println(sample_power);
            Serial.println(cnt_mean);
            cnt_mean++;
        }
        
        power[cnt_sample] = sample_power / cnt_mean;
        
        Serial.print("\n");
        Serial.print("Power per window of 5s: ");
        Serial.print(power[cnt_sample]);
        Serial.print("\n");        
        
        cnt_mean = 0;
        sample_power = 0;
        cnt_sample++;
        Serial.print("cnt_sample: ");
        Serial.print(cnt_sample);
        
    } else {
        Serial.println("Apply compression algorithm here & send.");
        cnt_sample = 0;
    }
}


