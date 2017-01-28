# Parts


### U1, ST SPV1040T, High efficiency solar battery charger with embedded MPPT, TSSOP8, , –40 to 125 °C 

One of the few single low voltage, small, and true MPPT ICs that also don't just shut down because it thinks its charging a Li battery. Surprisingly spacey (P CH MOSFET for switch).

Cons: Boost (although we need that), Iq of 80 uA is kind of high.

Notes: Configured to boost to 5.2V, which is why there's that flyback diode. Boost topology means it doesn't ever really shut off (even XSHUT won't turn it off) so that's why we have power transistors (Q1, Q2).


### U2, TI TCAN330GDCNT, SOT23-8, 3.3-V CAN Transceivers with CAN FD (Flexible Data Rate), –40 to 125 °C 

Choose this CAN transceiver because it operates on 3.3V, has a small package, and has both a low-current shutdown mode (2.5 uA) and a "silent" or listen only mode.

Cons: unknown radiation performance.


### U3, TI LM3671MF-3.3, SOT23-5, 2-MHz, 600-mA Step-Down DC-DC Converter (3.3V fixed), –40 to 125 °C

Chosen because it's got a nice package, has extremely low Iq (~18 uA) when running, and should be fine.

Cons: unknown radiation performance. Has a charge pump for the buck's N ch MOSFET, which isn't good. 

Notes: By default runs on the output of the MPPT IC (R15). It has an option to be run straight off the solar cell, which we might want to do for some reason we can't predict right now (R11). The divider is set to turn on enable at 3.0V, which we're not sure why? Really it should turn on at 3.3V. It has a 100% duty cycle option.


### U5, LT  LTC2990IMS#PBF, Quad I2C Voltage, Current and Temperature Monitor, MSOP-10, –40°C to 85°C

Quick and dirty way to read voltage, current, and precision temperature of the module, only a few uA in shutdown mode.

Cons: 1.8 mA when converting

Notes: TODO


### U6, ST STM32F042F6T7, TQFP-32, ARM Cortex-M0 USB line MCU with 32 Kbytes Flash, 48 MHz CPU, USB, CAN and CEC functions, –40 to 105 °C

STM32 which is our processor of choice, talks CAN, low power, especially when sleeping. TQFP package. The TSSOP is cute but doesn't have I2C + CAN available, and the QFN is just too high densitiy (0.5 mm) which is annoying. And we have *plenty* of space.

Cons: Not very space-y. High current draw when going full blast.

Notes: Programs using SWD, which is available through a cutouff in the PCB via CF2. Runs off a 8 MHz crystal. NRST has a built-in pull up, so no resistor necessary. In version 2: BOOT0 to a testpad, maybe pull to ground? Maybe run the USB out for DFU?


### C1, C2, C4, C5, C7, C8, C10, C15, 22µF ±10% 10V Ceramic Capacitor X7R, 1206, Generic part, chose  Murata GRM31CR71A226KE15L, -55 to 125°C

This is a generic 22 uF 1206 part used for bypassing the input and outputs of the SPV1040. The SPV switches very slowly (~ 100 kHz) so it needs giant caps. We obviously didn't want aluminum caps, so we stuck with an array of ceramics. IMPORTANT NOTE: probably not all of these need to be stuffed. We should experiment and see what's really necessary.

### R11, R15, 0 ohm 0805 resistors

These two 0 ohm resistors are power supply selection jumpers for the LM3671 and thus STM32 supply. Usually R15 is populated and R11 is NP, which means that the supply works off of the MPPT output. THis makes sense because MPPT... although we're losing power putting it through two switchers.

#### MCU 'C3' 100nF
#### MCU 'C22' 100nF
#### MCU 'C9' 100nF
### Cin
#### Use I = Imp, and assume 25 mV of input ripple, which is totally arbitrary?
#### .246A100000Hz * 0.025V = 98µF
#### Eval board uses 10 uF, so we may be way off here but there's no guidance about what an acceptable value is.
#### So we'll put 4x 22 uF in parallel , and we can get up to 88 uF which is probably enough. Choosing Murata GRM31CR71A226KE15L 22µF ±10% 10V Ceramic Capacitor X7R 1206 that's rated -55 to +125 C, because in the 1206 form factor it's < 2 mm and it's not a unicorn part.
### Cmppt-set
#### Filters Vin for MPPTSET. For R3 = 1k, should be <= 10uF but they use 100nF in the eval board? That's like 100x the 1 KHz tracking frequency? OK, whatever, go with their suggestion.
### Inductor 
#### L 9*10-6*Vmp4-2Imp
#### 9*10-6* 4.85V4-2*.23112.3µH    
#### Replacing Vmp with Voc for safety = 13.8 uH
#### Ipk will be <= Isc  which is ~ 250 mA
#### Vishay Dale IFSC1515AHER220M01  (Digi-Key  541-1407-1-ND)
#### 22µH Shielded Inductor +/- 20% 1.2A 315 mOhm Max 
#### Safely above what we need for inductance: 22 - 20% = 17.6 uH
#### -55 to +125, Fsrf = 5 MHz?? Not clear.
#### http://www.vishay.com/docs/34295/sc15ah01.pdf
#### MPPT 'R3' 1kΩ
#### MPPT 'R4' 1kΩ
#### MPPT 'R5' 1kΩ
#### MPPT 'R7' 866kΩ
#### MPPT 'R8' 274kΩ
#### MPPT 'C6' 100nF
#### MPPT 'C13' 1u
#### MPPT 'C12' 500p
### Cout
#### COUT1 vs COUT2???
#### Use I = Isc, I guess?, and assume 25 mV  again arbitrary?
#### .244 A100000Hz * 0.025V = ~ 98µF
####Eval board uses 10 uF, so we may be way off here but there's no guidance about what an acceptable value is.
####So, just like Cin: we'll put 4x 22 uF in parallel , and we can get up to 88 uF which is probably enough. Choosing Murata GRM31CR71A226KE15L 22µF ±10% 10V Ceramic Capacitor X7R 1206 that's rated -55 to +125 C, because in the 1206 form factor it's < 2 mm and it's not a unicorn part.
### R1 & R2, the Vctrl resistors
#### Output should be 5.0V, but the stupid schottky output diodes make everything terrible. So it's better to go to slightly higher, say 5.3V
#### That's R7 and R8 in the schematic
#### 5.0V: R7R8=51.25-1= 3  using 820k270k = 3.037 
#### Appnote says Ictrl should be between 2 - 20 uA, 820K + 270K = 4.6 uA
#### Well, that's fine, but we have that pesky schottky diode on the output that is going to kill (0.2,0.3,0.4)V depending on current. So let's hike that up a tad bit, to the highest recommended output of 5.2V.
#### 5.2V: R7R8=5.21.25-1= 3.16  using 866k274k = 3.161 which is < 1% error
#### Appnote says Ictrl should be between 2 - 20 uA, 866K + 274K = 4.6 uA
#### Power loss here is 5^2/(820+270) ~ 23 uW. Weird how they're concerned about power drop here, but sure, if you're dealing with uW sytem (not a 100 mW like we are) that makes sense.
### C2, the Vctrl filter cap
#### C12 in schematic
#### C1210*1Fsw*1R1//R2==0.000 000 000 492 = 492 pF~ 500 pF
### Rs, the current shunt resistor
#### 50mVIOUT(max)
#### 0.05V.256A=0.195
#### 0.05V.244A=0.205
#### Power on that is .256^2 * 0.2 ohms = 13 mW, which is a loss of ~ 1.3 %
#### Oh but wait; if Vctrl ever goes above 50 mV, the converter shuts down. That's not so good. More margin, please: 0.180 ohm
### R5(sense)=180m
### D1 (SPV1040 bypass diode) *and* the output diode
#### ST STPS1L40AY (DK 497-12286-1-ND)
#### Diode Schottky 40V 1A Surface Mount SMA (DO-214AC), -40°C ~ 150°C
#### Good tradeoff for Vf and Irev over temperature and voltage
### Dout, the output protection diode
#### So apparently this thing can go nuts and boost out a higher voltage if there's nothing like a battery holding it down? I guess? 
### LTC2990 RSense
#### REXT_MAX = 0.300V/IMAX = 0.3 / 250 mA = 1.2 Ω
#### No way! Way too high. Just use the 180 mΩ and call it good, we don't need all 14 bits anyway (for now).Shut Down N-Channel MOS
#### On N-Channel Fet
#### V/I/T 'C18' 100nF
#### V/I/T'C25' 100nF
#### V/I/T 'C14' 20uF
#### V/I/T 4.7k
#### V/I/T 10k 
### Shut down P-Channel MOSFET
#### SI4431CDY-T1-GE3
#### VGS(th) = 1V
#### MAX P = 1.6W
#### MAX V(drain) = -30V
#### MAX V(gate) = ±20V
### Shut Down 'R1' 10kΩ
### Shut Down 'R2' 100kΩ
### Voltage Reg (3.3V)
#### We want something with stupidly good Iq, so that when our output current is just a few dozen microamps, we're not powering the SPS IC in the mA regime. Also, should have an industrial temperature rating, and is really small, would be good. 
#### LM3671
#### Only downside: standard charge pump + N Ch MOSFET for the high side switch. We'll deal with this later in version 1?
#### VREG 665k
#### VREG 332k
#### VREG 'C23' 100nF
#### VREG 'C19' 100nF
#### VREG 'C24' 100nF
#### VREG 'C20' 4.7uF
#### VREG 10uH
#### VREG 'C21' 4.7uF
### Crystal ‘C16’ 20 pF
### Crystal 20 ‘C16’ pF
