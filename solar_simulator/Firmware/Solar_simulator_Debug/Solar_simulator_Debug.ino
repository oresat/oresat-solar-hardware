/*
 * Solar Simulator Debug Script
 * This Script is designed for hardware diagnostic/debugging of a  OreSat single solar simulator board
 * Does not output an accurage AM0 spectrum
 * for diagnostic purposes only
*/



  int Halogen = 9; //pin to control the halogen bulbs
  int PWMR = 0;  // pwm pin control the red LED channel
  int PWMG = 0;  //pwm pin to control the green LED channel
  int PWMB = 0;  //pwm pin to control the blue LED channel
  
  int LedBrightness = 0; //brightness setting for the LEDs 0-255, initilizes to 0 for safe startup
  int HalogenBrightness = 0;  //brightness setting for the halogens 0-255, initilizes to 0 for safe startup
  
void setup() {
    Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens
  
  pinMode(Halogen, OUTPUT);  //Pin for Halogen PWM

  pinMode(PWMR, OUTPUT);  //LED output pins
  pinMode(PWMG, OUTPUT);
  pinMode(PWMB, OUTPUT);
  
  
  analogWrite(PWMR, LedBrightness); //initializes the leds to LedBrightness
  analogWrite(PWMG, LedBrightness);
  analogWrite(PWMB, LedBrightness);
  
  analogWrite(Halogen, HalogenBrightness); //intializes the halogens to HalogenBrightness

  delay(500);
  Serial.print('enter an integer between 0-255 to define the brightness'); 
}

void loop() 
{
  if(Serial.available()>0)
  {
    LedBrightness=Serial.read();  //scans in input from user to define new brightness
    HalogenBrightness=LedBrightness;  //temporarily link halogen and LedBrightness

    analogWrite(PWMR, LedBrightness); //sets leds to LedBrightness
    analogWrite(PWMG, LedBrightness);
    analogWrite(PWMB, LedBrightness);
  
    analogWrite(Halogen, HalogenBrightness); //sets halogens to HalogenBrightness

    Serial.print('Input received, brightness set to: ');
    Serial.println(LedBrightness, DEC);
  }
}
