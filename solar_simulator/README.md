# Solar Simulator

# The Problem:  AKA Oh dear god why is everything so expensive

Because we wanted to test our solar panels in our thermal vacuum chamber, we needed a solar simulator that could simulate the AM0 light spectrum while also being compact, power efficient, and (most importantly) cheap!

Normal incandescent solutions were too bulky to fit in our tiny vacuum chamber, they require a lot of power, and dissipate a whole lot of heat into the system.  LED solutions do exist, but they are insanely expensive. So-being the loveable open source rogues that we are- decided to build our own!

# The Design
### LED SelectionThe wavelengths of light we care about ranges from about 376.5 nm - 899 nm (this is the approximate), meaning we can discard wavelengths in the AM0 spectrum outside of these bounds.  

We are only using three LED channels for our design (R, G, and B) most commercial simulators use way more channels than we do, but because our panels have a relatively flat response curve, and we don't care *that* much about super precision, we think we can get away with just 3.  So we split the wavelength spectrum into 3 roughly equal bands, and sum up the total irradiance found within the band.  This will give us the total irradiance needed for each band of LEDs.

Blue Irradiance(376.5 nm - 504.5 nm) = 221.9 W/m^2
Green Irradiance(505.5 nm - 637 nm) = 233.8 W/m^2
Red Irradiance(639 - 899 nm) = 161.5 W/m^2

Each channel is composed of CREE X-QE LEDs, because they are insanely small and power efficient and come in the wavelengths that work for us ( 440 nm, 520 nm, and 630 nm respectively).  In future revs we may shift our bands to better fit these wavelengths.  

### Driver Selection
Each channel is driven by a TPS92512 LED driver, since they can push stupid amounts of power at a very high frequency, and can be controlled with either a low frequency PWM from a microcontroller, or an analog input.  Each channel is in parallel and calculations are done assuming 56V Vin, meaning that the Vpp should be capable of 56V 3A. (NOTE: We could get away with lower voltages, but using 56V allows us to use a higher switching frequency of 1 MHz)

### Microcontroller
We are using an Arduino Nano (Atmega328P) as a daughter board to control the 3 LED LM3404HVs via an I2C DAC (MCP4728), as well as reading the 4 thermistors and reporting it over USB.  It is quick, dumb, and easy.  In the future we may move to an embedded microcontroller but this is easy enough for now.

 # Component Calculations

 Vin = 56 V

 Vout = 48.2 V (worst case)

 switching frequency = fsw = 1 MHz

* Output Inductor
  * NOTE: Iripple must be at least 75 mA for reliable operation.  400 mA chosen to decrease size of inductor.
  * L = (Vout * (Vin - Vout) ) / (Iripple * Vin * fsw)
      = (48.2 * (56-48.2) )/ (.4 * (56) * (10^6) )
      = 170 uH
* Maximum Duty Cycle
  * D = Vout/Vin
      = 56/48.2
      = 86%
* Input Capacitance
  * Note: ΔVin is assuming a 5% ripple on Vin
  * Cin = (Iled * D * (1-D) )/(ΔVin * fsw)
        = (1 * .86 * .14)/(2.8*10^6)
        = 43 nF
* Dynamic resistance of LEDs
  * Rled = (ΔVled/ΔIled) * #LED
         = .5 * 15
         = 7.5 Ω
* Output Capacitance
  * Zcout = (Rled * ΔI) / (Iripple - ΔI)
          = (7.5 * .05) / (.2 - .05)
          = 2.5 Ω
  * Cout = 1 / (2 * π * fsw * Zcout)
         = 1 / (2 * π * 10^6 * 2.5)
         = .15 uF
* Power Dissipation
  * Psw = D * Rds * Iled^2
        = .86 * .28 * 1^2
        = .24 W
  * Piq = Vin * (400 * 10^-6 + (.002 * fsw) / 10^6)
        = 56 * (400 * 10^-6 +  (.002*10^6) / 10^6)
        = .13 W
  * Pac = .73 * 10^-9 * fsw * Vin^2 * Iled
        = .73 * 10^-9 * 10^6 * 56^2 * 1
        = 2.29 W
  * Ptotal = (Psw + Piq + Pac) * #LEDDrivers
           = (.24 + .13 + 2.29) * 3
           = 2.66 * 3
           = 7.98 W 
