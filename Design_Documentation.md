## SOLAR MODULE v0: SPV1040 DESIGN
&nbsp;&nbsp;&nbsp;&nbsp;The SPV1040 is a switching boost regulator already utilized in other Cubesats.
The input will be 5 Alta Cell Gallium Arsenide solar cells wired in series.
The output will be a 5V DC signal with output ripple voltage of ≅ 25mV.
While the SPV1040 is unable to give voltage current and temperature, the LTC2990 will be utilized to provide each of these measurements.
The LTC2990 is a single 10 pin V/I/T to I2C and will communicate to the L3 board via this protocol.
The Gallium Arsenide solar cells used have been tested up to 1000 W/m^2 irradiance.
The real mean irradiance in space is 1366 W/m2.
While the increase in power and current are relatively linear with increased
 irradiance the voltage will be somewhat constant (if not slightly decreased).
However since our cells have not been tested at such high altitudes we do not want to rely on theoritcal power
So we are designing for our worst-best case scenario, 1000 W/m^2
Due to structural limitations all components must be =< 2 mm.

#### Inputs (from datasheet with AM0 numbers)#
    Voc =  Ncells * Voc = 5 * 1.09V = 5.45V
    Vmp = Ncells * Vmp = 5 * 0.97V = 4.85V
    Isc = 244 mA 
    256 mA with no cover, but we're assuming a cover
    Imp  = 231 mA
    No cover = 236 mA but assume cove
    Pmax/mp = Ncells * Pmp = 5 * 0.223W = 1.12 W
#### Considerations:
Perhaps the core of our design is the solar cells themselves.  For this
project we chose to desing for use with Gallium Arsenide Cells from 
##### Alta Devices
    250 W/m^2 @ 28.8% eff.
Which we considered an improvement from Andrew's monocrystalline
#####Silicon solar cells:
    ~15% efficiency
    Voc ~ 0.6 V (link) but we should measure this.
    2.91 Voc, .151 Isc (Tested,  5s, full sun, 60 deg. F, 2/24/2016)
It is worth it to note that the efficiency drops by 12-15% at
temperatures above 50 C (monocrystalline)

Such discusions lead us to our next issue:
##### How many cells per panel?
We clearly want >> 1 cell, because 0.7V isn't enough voltage for most MPPTs.
We probably want/can get 5-7 cells with SPV1040 MPPT however we probably won't get near the charge voltage of the 
LiPo batteries, which is around ~ 16.8V, because that would
require like 24 cells, which seems.. like a lot of cells for one side.
So... somewhere between say 3 - 15 V on the Voc of the panel.  
Due to limitations of the size of our array we decided to use 5 cells in series which also means we
need a boost or buck-boost MPPT.
From the list below the best bet seems to be SPV1040 as it has been tested in other cubesats and seems
to meet our design requirements.  3 revs built and tested, with new cells this may not be the best option,
however it is likely the best COTS option available.
##### Maximum Power Point Trackers
    ZSPM 4521
    -seems to do everything we need.
    -Contains automatic shutdown algorithm that can’t be bypassed according to the manufacturer.
    
    ZMDI ZSPM4523AA1W
    -Can’t use due to automatic shutdown
    
    ZMDI ZSPM4521
    -Can’t use due to automatic shutdown
    
    LT LTC4121
    -"MPPC", not MPPT
    -ZSPM4523AA1WBuck
    
    LT LTC3105
    -"MPPC", not MPPT
    
    LT LTC3106
    -"MPPC", not MPPT
    -Has "powerpath" for a primary battery (don't care)
    
    LT LTC3129
    -"MPPC", not MPPT
    
    TI SM72442
    -Complicated
    -i2c
    -buck/boost
    
    TI SM72445
    -Also complicated
    -i2c
    -buck/boost
    
    ST SPV1020 - Interleaved DC-DC boost converter with built-in MPPT algorithm
    -Real MPPT
    -Boost, Voc = 6.5 - 40 V
    -Talks SPI
    -Probably too biggish -- meant for large panels
    
    ST SPV1040 - High efficiency solar battery charger with embedded MPPT
    -Real MPPT
    -Boost, Voc = 0.3 V to 5.5 V
    -Resurected
    
    ST SPV1050 - Ultralow power energy harvester and battery charger
    -Buck-boost, Voc = 75 mV - 18V
    -Not a true MPPT, looks like it multiplies by Voc</pre>
#### Sensor IC
The only problem with the SPV1040 is that it can't tell us the voltage (V) and current (I) and temperature (T) 
of the solar array. We could monitor each solar array output (V,I,T) using the single chip LTC2990, which is a 
single 10 pin V/I/T to I2C converter and is being used on the LTC3.  From talking to others in the industry
it seems that cross-board I2C is not reliable in cubesat applications so we decided to add a CAN bus to the design.
We will use a µC that speaks I2C and CAN to take in the telemetry from the sensor on the I2C bus and ship it to
the CCC module via CAN.

#### Microcontroller
    STM32F042F6
    -Moving forward with this microcontroller.
    -We had tried to use a smaller TSSOP version of the µC however it couldn't handle both I2C/CAN
    -We like this controller because we know it and are using it elsewhere in the satellite
    

#### Research
µCs
Look for research on loss/gain of mppt and research whether or not it’s possible to delete it from power module.
We probably need to just build it and test.

Smallsat conference.  San luis bisbo and logan, april
µCs
We will need a low power microcontroller that speaks CAN and can manage PWM. There aren't a lot of choices, boiled down to NXP, ATMega32M4, and of course an STM.

#### Battery / Power management
We had initially toyed with the idea of making the solar array and the battery charger one unit
however we decided against it to maintain our modularity.
