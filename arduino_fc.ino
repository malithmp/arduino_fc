// Interrupt Pin Ids
const byte INTERRUPT_1 = 2;
const byte INTERRUPT_2 = 3;

volatile unsigned long int pin_2_start;  // When channel 1 went high
volatile unsigned long int pin_3_start;  // When channel 2 went high

volatile unsigned long int channel_1_period; // PPM signal period channel 1
volatile unsigned long int channel_2_period; // PPM signal period channel 2

volatile unsigned long int channel_1_width;  // PPM signal width channel 1: should be 20ms
volatile unsigned long int channel_2_width;  // PPM signal width channel 2: should be 20ms

// Keep track of the lowest pin valus seen so we can calculate the diff
volatile unsigned long int ch1_min;  // channel 1 lowest ppm period
volatile unsigned long int ch2_min;  // channel 2 lowest ppm period

void setup() {
  Serial.begin(9600);
  
  pin_2_start      = 0;
  pin_3_start      = 0;
  channel_1_period = 999999;
  channel_2_period = 999999;
  channel_1_width  = 0;
  channel_2_width  = 0;

  ch1_min = 999999;
  ch2_min = 999999;
  
  pinMode(2, INPUT);
  pinMode(3, INPUT);
    
  attachInterrupt(digitalPinToInterrupt(2), ch1_ppm_change, CHANGE);
  attachInterrupt(digitalPinToInterrupt(3), ch2_ppm_change, CHANGE);

  Serial.println("begin");
}

void ch1_ppm_change()  { 
  int x = digitalRead(2);
  unsigned long int t = micros();
  
  if (x == HIGH) { // Rising edge
    channel_1_width = t - pin_2_start;
    pin_2_start = t;
  }else{           // Falling edge
    channel_1_period = t - pin_2_start;
  }
}

void ch2_ppm_change()  { 
  int x = digitalRead(3);
  unsigned long int t = micros();
  
  if (x == HIGH) { // Rising edge
    channel_2_width = t - pin_3_start;
    pin_3_start = t;
  }else{           // Falling edge
    channel_2_period = t - pin_3_start;
  }
}

void track_mins(){
  if (ch1_min > channel_1_period) {
     ch1_min = channel_1_period;
  }

  if (ch2_min > channel_2_period) {
     ch2_min = channel_2_period;
  }
}

void mix_signals() {
  long int ch1 = channel_1_period - ch1_min;
  long int ch2 = channel_2_period - ch2_min;

  String chs="|CH1|:" + (String)ch1 + " |CH2|:" + (String)ch2;
  Serial.println(chs); 
}

void loop() {
  // put your main code here, to run repeatedly:
  track_mins();
  mix_signals();
  //String ch1="|CH1| period:" + (String)channel_1_period + " width:" + (String)channel_1_width + " min:" + (String)ch1_min;
  //String ch2="|CH2| period:" + (String)channel_2_period + " width:" + (String)channel_2_width + " min:" + (String)ch2_min;
  
  //Serial.println(ch1); 
  //Serial.println(ch2);
  delay(500);
 }
