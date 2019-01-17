// Interrupt Pin Ids
const byte INTERRUPT_1 = 2;
const byte INTERRUPT_2 = 3;

volatile unsigned long int ch1_ppm_start_time;  // When channel 1 went high
volatile unsigned long int ch1_ppm_finish_time; // When channel 1 went low
volatile unsigned long int ch2_ppm_start_time;  // When channel 2 went high
volatile unsigned long int ch2_ppm_finish_time; // When channel 2 went low


void setup() {
  Serial.begin(9600);
  
  ch1_ppm_start_time  = 0;
  ch1_ppm_finish_time = 0;
  ch2_ppm_start_time  = 0;
  ch2_ppm_finish_time = 0;

  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(2), ch1_ppm_rising, RISING);
  attachInterrupt(digitalPinToInterrupt(2), ch1_ppm_falling, FALLING);

  pinMode(3, INPUT);
  attachInterrupt(digitalPinToInterrupt(3), ch2_ppm_rising, RISING);
  attachInterrupt(digitalPinToInterrupt(3), ch2_ppm_falling, FALLING);

  Serial.println("begin");
}

void ch1_ppm_rising()  { 
  ch1_ppm_start_time++;
}

void ch1_ppm_falling() { 
  //ch1_ppm_finish_time++;
}
void ch2_ppm_rising()  { 
  ch2_ppm_start_time++;
}

void ch2_ppm_falling() { 
  //ch2_ppm_finish_time++;
}

int ch1_pulse() { return (ch1_ppm_finish_time - ch1_ppm_start_time);} 
int ch2_pulse() { return (ch2_ppm_finish_time - ch2_ppm_start_time);} 

void loop() {
  // put your main code here, to run repeatedly:
  delay(100);
  
  String ch1="|CH1|" + (String)ch1_pulse();
  String ch2="|CH2|" + (String)ch2_pulse();
  
  Serial.println(ch1);
  Serial.println(ch2);

  delay(100);
  
 }
