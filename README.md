# OreSat Solar Modules

This repo contains the design for [OreSat's](oresat.org) solar modules. Part of OreSat's design is a module bus system that spans 1 - 3 U, so each array is its own 1U "panel". Oresat0, a 1U CubeSat, thus has 4 solar modules, and OreSat1, a 2U CubeSat, has 8. This approach has pretty severe drawbacks in terms of solar cell coverage area, but it's extremely flexible for having one design across a bunch of different designs. One nifty part of this design is that each 1u panel has its own **true** maximum power point tracker, with a software-defined MPPT algorithm. We're MPPT elitists - we eschew maximum power point "controllers" and think if it's not doing true power point optimization, you're just doing it wrong.

That and coffee. You're all doing coffee wrong, too, but we don't hold that against you, you don't live in Portland, we understand.

![Solar modules on OreSat0](https://github.com/oresat/oresat-solar/blob/master/images/oresat0-solar-modules.jpg)
![Top (solar cells) and bottom (circuitry) of the solar modules](https://github.com/oresat/oresat-solar/blob/master/images/oresat-solar-modules.jpg)


## Solar Cells

### GaAs Cells
[Spectrolab XTE-SF GaAs solar cells](https://www.spectrolab.com/photovoltaics/XTE-SF_Data_Sheet.pdf). Yeah, they're expensive. But you can't yet get anything close to that kind of power output.

### Silicon Cells
Of course we use the [ANYSOLAR IXOLAR series](https://www.anysolar.biz/Gen3) of cells.

## Design Notes

As usual, we have no clue what we're doing, but we're _particularly_ excited about this MPPT design. We have an inner loop controlled at 1.4 MHz by an LT1618 boost converter, and an outer loop controlled by firmware in the STM32 microcontroller. With firmware control, we can do cool things like variable step incremental conductance algorithms. However, VS-IC is hard, so what we ended up with is P&O because that just works. One day we'll be cooler and try to more carefully implement VS-IC. 

Full design notes can be found in the [OreSat Solar Module Design Notes](https://docs.google.com/document/d/1mogZjYhJievwLsnVkg4Q0sEF9xPMA5q7KPciky3YWKE/edit?usp=sharing).

## Versions
### GaAs Modules
- v5.4 - IN PROGRESS. Moved to KiCAD, small improvements on the 5.3.
- v5.3 - Finally got the damn upsidedown TMP101 footprints right. **Successfully flown on OreSat0 and OreSat0.5!**
- v4.0 - Switched from Alta Devices (RIP) to Spectrolab and upgrade to the STM32F091
- v3.0 and earlier not worth mentioning.
### Silicon Modules
- v1.1 - IN PROGRESS. Fixes v1 issues.
- v1.0 - First silicon modules, in KiCAD! Lots of serious issues, do not use.

## LICENSE

Copyright the Portland State Aerospace Society, 2022.

This source describes Open Hardware that is licensed under CERN-OHL-S v2, or any later version.

You may redistribute and modify this source and make products using it under the terms of the CERN-OHL-S v2 (https://ohwr.org/cern_ohl_s_v2.txt).

This source is distributed WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING OF MERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A PARTICULAR PURPOSE. Please see the CERN-OHL-S v2 for applicable conditions.

Source location: https://github.com/oresat/

If you require a different license for this open hardware project, please contact us at [oresat@pdx.edu](mailto:oresat@pdx.edu).
