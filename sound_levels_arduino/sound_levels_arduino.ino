const int sample_window = 50; // this is the size of the sample window in ms
const int ref_val = 230; // this value is a reference for the p2p values
// the compression algorithm will be applied to the deviations from this value
const int no_samples = 150; // after 150 received samples, we compress & send them
int p2p_deviation[150];
unsigned int sample; // stores the level of a measured sample
unsigned int cnt_sample = 0;

void setup()
{
    Serial.begin(9600);
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

    if (cnt_sample < no_samples) {
        while (millis() - loop_start < sample_window) {        
            sample = analogRead(0); // the mic is connected to Arduino's Analog Input pin no. 0
            if (sample > max_level) {
                max_level = sample;
            } else if (sample < min_level) {
                min_level = sample;
            }
        }
        Serial.print("\n");
        Serial.print("cnt_sample is: ");
        Serial.print(cnt_sample);
        Serial.print("\n");
        cnt_sample++;
        peak_to_peak = max_level - min_level;
        Serial.print("\n");
        Serial.print("peak_to_peak is: ");
        Serial.print(peak_to_peak);
        Serial.print("\n");
        p2p_deviation[cnt_sample] = ref_val - peak_to_peak; // calculate deviation and store in vector
        Serial.print("\n");
        Serial.print("deviation is: ");
        Serial.print(p2p_deviation[cnt_sample]);
        Serial.print("\n");
    } else {
        Serial.println("Apply compression algorithm here & send.");
        cnt_sample = 0;
    }
}


