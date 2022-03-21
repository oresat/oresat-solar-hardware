# OreSat Solar Modules

This repo contains the design for [OreSat's](oresat.org) solar modules. Part of OreSat's design is a module bus system that spans 1 - 3 U, so each array is its own 1U "panel". Oresat0, a 1U CubeSat, thus has 4 solar modules, and OreSat1, a 2U CubeSat, has 8. This approach has pretty severe drawbacks in terms of solar cell coverage area, but it's extremely flexible for having one design across a bunch of different designs. One nifty part of this design is that each 1u panel has its own **true** maximum power point tracker, with a software-defined MPPT algorithm. We're MPPT elitists - we eschew maximum power point "controllers" and think if it's not doing true power point optimization, you're just doing it wrong.

That and coffee. You're all doing coffee wrong, too, but we don't hold that against you, you don't live in Portland, we understand.

![Solar modules on OreSat0](https://github.com/oresat/oresat-solar/blob/master/images/oresat0-solar-modules.jpg)
![Top (solar cells) and bottom (circuitry) of the solar modules](https://github.com/oresat/oresat-solar/blob/master/images/oresat-solar-modules.jpg)


## Solar Cells

[Spectrolab XTE-SF GaAs solar cells](https://www.spectrolab.com/photovoltaics/XTE-SF_Data_Sheet.pdf). Yeah, they're expensive. But you can't yet get anything close to that kind of power output. Luckily, our MPPT doesn't really care what cells it uses, as long as the Vmp is > 3 V and < 6 V, so you could use Silicon if you wanted to.

## Design

As usual, we have no clue what we're doing, but we're _particularly_ excited about this MPPT design. The [Analog Devices LT1618 Constant-Current/Constant-Voltage 1.4MHz Step-Up DC/DC Converter](https://www.analog.com/en/products/lt1618.html) happens has an optional "Iadj" input, which allows the user to select a current limit.  Using this current limit, an INA226 V/I sensor, and the DAC onboard the STM32F091, we can whip together a low power software-controlled MPPT. Briefly, the M0 calculates the MPPT using data from the INA226, and uses its DAC to output an analog voltage on the LT1618's Iadj. So we really control the cell's Imp. The 1.4 MHz SPS handles all of the fast control, and we occasionally wake up the STM32 (at 10 Hz), calculate a new MPP, and then go back to sleep.

With software control, you can do cool things like variable step incremental conductance algorithms. However, VS-IC is hard, so what we ended up with is P&O because that just works. One day we'll be cooler and try to more carefully implement VS-IC. 

The M0 reports the V/I data (along with temperature values from TMP101) to our C3 flight computer over CAN. You can find all of the design and CAD files in the ['1u_panel' folder](https://github.com/oresat/solar/tree/master/1u_panel).
bat

## Versions

- v5.3 - Finally got the damn upsidedown TMP101 footprints right.
- v4.0 - Switched from Alta Devices (RIP) to Spectrolab and upgrade to the STM32F091
- v3.0 and earlier not worth mentioning.
   
## LICENSE

Copyright the Portland State Aerospace Society, 2022.

This source describes Open Hardware that is licensed under CERN-OHL-S v2, or any later version.

You may redistribute and modify this source and make products using it under the terms of the CERN-OHL-S v2 (https://ohwr.org/cern_ohl_s_v2.txt).

This source is distributed WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING OF MERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A PARTICULAR PURPOSE. Please see the CERN-OHL-S v2 for applicable conditions.

Source location: https://github.com/oresat/

If you require a different license for this open hardware project, please contact us at [oresat@pdx.edu](mailto:oresat@pdx.edu).
