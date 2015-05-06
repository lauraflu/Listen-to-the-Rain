#define SIZE 800

const int sample_window = 1000; // this is the size of the sample window in ms
int sample; // stores the level of a measured sample
unsigned int i = 0;
double power = 0;
int sample_vector[SIZE];

// Define various ADC prescaler
// The ADC clock needs  to be between 50 kHz and 200  kHz for 10 bit accuracy.
// With the 128 prescaler, the ADC's clock will run at 125 kHz. A normal 
// conversion in the ADC takes 13 clock cycles, so the sample speed will be 
// 125 kHz / 13 ~= 9600 Hz => maximum 9600 samples / sec. 
// With the 64 prescaler, the ADC's clock will run at 250 kHz, so the sample
// speed will be 250 kHz / 13 ~= 19 000 Hz, so we'll get about as many samples/sec.
// We the 64 prescaler, we can get a samples once every 60 - 64 us.
// In reality, depending on what other operations we perform in the sampling
// loop, we'll have less samples/sec.

const unsigned char PS_64 = (1 << ADPS2) | (1 << ADPS1);
const unsigned char PS_128 = (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

void setup()
{
    Serial.begin(9600);
    
    // set up the ADC
    ADCSRA &= ~PS_128;  // remove bits set by Arduino library
    ADCSRA |= PS_128;    // set our own prescaler to 64 
}

void loop()
{
  // millis() is a function that returns the number of milliseconds since the program
  // started, as an unsigned long
  
//  Serial.println("Say something");

  i = 0;
  power = 0;
  unsigned long loop_start = millis();
  while (millis() - loop_start < sample_window) {
    sample = analogRead(0) - 512; // the mic is connected to Arduino's AI pin no. 0
    // we calculate the values relative to the level 512
    //if (i < SIZE)
    //  sample_vector[i] = sample;
    
    power += sample * sample;
    i++;
  }
   
  power = power / i + 1;
  
  Serial.println(power);
  //Serial.println("number samples: ");   
  // Serial.println(i);
  /*
  for (i = 0; i < SIZE; i++) {
    Serial.println(sample_vector[i]);
  }
  */
  // send the value of the power over wireless to the second Arduino 
}


