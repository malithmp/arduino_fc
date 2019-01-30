// Interrupt Pin Ids
const byte INTERRUPT_1 = 2;
const byte INTERRUPT_2 = 3;

volatile unsigned long int pin_2_start;  // When channel 1 went high
volatile unsigned long int pin_3_start;  // When channel 2 went high

volatile unsigned long int channel_1_period; // PPM signal period channel 1
volatile unsigned long int channel_2_period; // PPM signal period channel 2

volatile unsigned long int channel_1_width;  // PPM signal width channel 1: should be 20ms
volatile unsigned long int channel_2_width;  // PPM signal width channel 2: should be 20ms


void setup() {
  Serial.begin(9600);
  
  pin_2_start      = 0;
  pin_3_start      = 0;
  channel_1_period = 0;
  channel_2_period = 0;
  channel_1_width  = 0;
  channel_2_width  = 0;

  pinMode(2, INPUT);
  //pinMode(3, INPUT);
    
  attachInterrupt(digitalPinToInterrupt(2), ch1_ppm_change, CHANGE);
  //attachInterrupt(digitalPinToInterrupt(3), ch2_ppm_change, CHANGE);

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


void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  
  String ch1="|CH1| period:" + (String)channel_1_period + " width:" + (String)channel_1_width;
  
  Serial.println(ch1);

  delay(100);
  
 }
