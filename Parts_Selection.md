
# Parts
### STM32F042F6
#### In the TQFP. The TSSOP is cute but doesn't have I2C + CAN available, and the QFN is just too HD (0.5 mm) which is annoying. And we have *plenty* of space.
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
