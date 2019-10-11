const int PWMR = 9; //Pin assignments for PWM channels
const int PWMG = 10;
const int PWMB = 11;

const int TempSenseR = 24;  //Red LED driver
const int TempSenseG = 23;  //Green LED driver
const int TempSenseB = 25;  //Blue LED driver
const int TempSenseLED = 26; //LED array

const float ThermalCutoff = 60; //Defines automatic shutoff temperature in celsius

void DataDump (int SimulatorStatus, float RedTemp, float GreenTemp, float BlueTemp, float LEDTemp)
{
  //TODO:Write script to read data and display on console and not shitty serial monitor
  //Prints relevant data to serial monitor
  Serial.println("SimulatorStatus: " + (char) SimulatorStatus);
  Serial.println("\n\nTemperatures(Temps in C)");
  Serial.println("Red Driver: " + (char) RedTemp);
  Serial.println("Green Driver: " + (char) GreenTemp);
  Serial.println("Blue Driver: " + (char) BlueTemp);
  Serial.println("LED Array: " +(char) LEDTemp);
}
float GetTemp(int TempPin)
{
  float PinTemp 
  //TODO: Write function to read the voltage from the given pin and translate to a temperature(measured in clesius).  Store the final temperature in PinTemp
  return PinTemp
}
void setup() {

  //declares the pwm output for the R, G, and B channels
  pinMode(PWMR, OUTPUT);
  pinMode(PWMG, OUTPUT);
  pinMode(PWMB, OUTPUT);

  //sets up the ADC pins to read from thermisters
  pinMode(TempSenseR, INPUT);
  pinMode(TempSenseG, INPUT);
  pinMode(TempSenseB, INPUT);
  pinMode(TempSenseLED, INPUT);

  Serial.begin(115200);


}
int SimulatorStatus = 0; //Stores the current state of the simulator (eg off, simulation1, emergency shutdown
float RedTemp, GreenTemp, BlueTemp, LEDTemp; //stores the most recent temperature of each thermister in celsius
void loop()
{
  if (Serial.available() > 0) //Simulator is active
  {
    SimulatorStatus = Serial.parseInt();
    if (SimulatorStatus == 1) //Constant AM0 spectrum
    {
      while (SimulatorStatus != 0)
      {
        analogWrite(PWMR, 125);
        analogWrite(PWMG, 125);  //TODO: calculate correct ratios to match AM0 spectrum
        analogWrite(PWMB, 125);
      }
      if (Serial.parseInt() == 0)
      {
        SimulatorStatus = Serial.parseInt();
      }
    }

    else if (SimulatorStatus == 2) //1 Min Cycle (brightness slowly increses then dims)
    {
      while (SimulatorStatus != 0)
      {
        for (int i = 0; i <= 255; i++)
        {
          analogWrite(PWMR, i);
          analogWrite(PWMG, i); //TODO: Calculate corrections so that spectra is right, also correct the max value for i
          analogWrite(PWMB, i);
          delay(10);
          if (Serial.parseInt() == 0)
          {
            SimulatorStatus = Serial.parseInt();
            break;
          }
        }

      }
    }
  }
  else //Simulator is in standby mode
  {
    //Gathers appropriate data of simulator while in standby
        RedTemp=GetTemp(TempSenseR);
        GreenTemp=GetTemp(TempSenseG); //TODO: Write temp sense function and calibrate thermistors
        BlueTemp=GetTemp(TempSenseB);
        LEDTemp=GetTemp(TempSenseLED);

    DataDump(SimulatorStatus, RedTemp, GreenTemp, BlueTemp, LEDTemp); //Transmits data over serial to master
  }

}
