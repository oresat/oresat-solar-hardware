# OreSat Solar Module v2

## Everything is terrible (architecture)

The system architecture of OreSat is weird, and possibly seriously dumb. However, it has a lot of advantages that, despite it's dumbness, are a system-win. One of those dumb ideas that might be either a terrible, terrible mistake or a brilliant stroke of insight (emphasis, possibly, on the stroke) is that the Vbus is based on the Vbat which is a single Lipo cell. Meaning, the Vbus ranges from 3.0 to 4.2 V. Yep. We told you. Brilliant or dumbass. Ask us in 2020 and we'll let you know.

Base on that, we wanted a maximum power point tracer (MPPT) that could take our solar array input and buck/boost that to the 4.2V necessary to charge the battery. Thus there's only one SPS between the array and the batteries, and it's MPPT. A true MPPT, mind you, not one of these namby pamby "70% Voc" maximum power point "controllers".

Finally, we were very interested in a modular array that could stand on it's own, even on a 1U, so we decided to make a single module that stood on its own and could be parallelled with other modules.

## Solar array

The array will be Alta Devices Inc Gallium Arsenide (GaAs) chemical vapor deposition (CVD) thin film solar cells wired in series in a single "5 cell module". From their datasheet, which includes AM0 irradiance figures(!):

    Voc =  Ncells * Voc = 5 * 1.09V = 5.45V
    Vmp = Ncells * Vmp = 5 * 0.97V = 4.85V
    Isc = 244 mA 
    256 mA with no cover, but we're assuming a cover
    Imp  = 231 mA
    No cover = 236 mA but assume cover
    Pmax/mp = Ncells * Pmp = 5 * 0.223W = 1.12 W

## MPPT ICs

Requirements:

- (4.0, 4.85, 5.45) V input from the Alta Devices array.
- 3.0 - 4.2 V output connected directly to our LiPo cells -- we don't want a separate battery charger.
- Thus, it needs to be a buck/boost, or at least a buck, supply.
- MPPT, not MPPC.
- Single IC if possible.

We choose the IDT (previoulsy ZMDI) **ZSPM4521** "DC/DC synchronous switching lithium-ion (Li-Ion) battery charger with fully integrated power switches, internal compensation, and full fault protection. It uses a temperature-independent photovoltaic maximum power point tracking (MPPT) function to optimize power output from the source during Full-Charge Constant-Current (CC) Mode."

It's the ONLY MPPT IC that bucks: We need to go from ~ 4.85V down to 4.2 V. This is terrible, because ZSPM4521 is End-Of-Life (EOL) and is only available on the gray market :(

- ZMDI ZSPM4523 -- for super caps only, doesn't do LiPos.
- LT LTC4121 -- "MPPC", not MPPT
- LT LTC31XX -- "MPPC", not MPPT
- TI SM72442 -- stupidly complicated, but it is buck/boost.
- TI SM72445 -- Also complicated
- ST SPV10X0 -- Boost only, can't buck.

For configuration and parts, see the [ZSPM4521 design notes](ZSPM4521.md).

## Sensor IC

We choose the LT *LTC2990* to measure voltage, current, and temperature from the solar array. The LTC2990 talks I2C to our uC. It uses a 2N2903 transistor as a diode to do temperature measurement, which is cool because we can put that _in_ the board in a slot and try and get the actual array temperature. See the [LTC2990 design notes](LTC2990.md).

## Microcontroller

For many reasons, we're using the ST **STM32F042K6**, which is a TQFP 32 pin Cortex M0 IC which talks CAN. We're using it all over the place on OreSat. And we choose the TI **TCAN330** as the CAN transceiver.

## 3.3 V SPS

After looking at a billion 3.3V switcher ICs, we really like the TI **TPS63020**. The final system footprint is large, but it does buck-boost so that we can get 3.3V even if our batteries are down to their 3.0V minimum voltage. Also, temporary brownouts should be OK given the boost and the giant capacitor banks the TPS63070 requires. See the [TPS63070 design notes](TPS63070.md)

## OreSat Shutdown

The Remove Before Flight (RBF) and rail inhibit switches all need to shut down OreSat. We have a "open collector" shutdown system; pulling the line to ground shuts down OreSat. The STM can decide to shut down it's local panel, too.

Note that we want the ability to power cycle all the things; luckily, because space, the ZSPM4521 will be deep power cycled every time we go in the shadow of the earth. At that point, the hole solar board should power off because of the LTC4411 ideal diodes. 

We choose regular 1N4448 diodes for the shutdown path because of the horrific leakage current of Schottkey diodes at high temperatures. They leavek **10s of mA!!11!!**. That's a lot. So we choose a silicon diode, run at very low current, so the most the Vf will be is 0.7 V even at very low temperatures. We have to be careful, because the ZSPM4521's EN line has a minimum V_L of 0.8V, so we need to be well under that.



