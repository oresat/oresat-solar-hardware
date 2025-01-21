# OreSat Solar Modules

This repo contains the design for [OreSat's](oresat.org) solar modules. Part of OreSat's design is a module bus system that spans 1 - 3 U, so each array is its own 1U "panel". Oresat0, a 1U CubeSat, thus has 4 solar modules, and OreSat1, a 2U CubeSat, has 8. This approach has pretty severe drawbacks in terms of solar cell coverage area, but it's extremely flexible for having one design across a bunch of different designs. One nifty part of this design is that each 1u panel has its own **true** maximum power point tracker, with a software-defined MPPT algorithm. We're MPPT elitists - we eschew maximum power point "controllers" and think if it's not doing true power point optimization, you're just doing it wrong.

That and coffee. You're all doing coffee wrong, too, but we don't hold that against you, you don't live in Portland, we understand.

We've flown our GaAs solar cell design, and are currently workingon our silicon design.

All version, status, design notes, and construction info can be found in the [OreSat Solar Module Design Notes](https://docs.google.com/document/d/1mogZjYhJievwLsnVkg4Q0sEF9xPMA5q7KPciky3YWKE/edit?usp=sharing).

![Solar modules on OreSat0](https://github.com/oresat/oresat-solar/blob/master/images/oresat0-solar-modules.jpg)
![Top (solar cells) and bottom (circuitry) of the solar modules](https://github.com/oresat/oresat-solar/blob/master/images/oresat-solar-modules.jpg)

## LICENSE

Copyright the Portland State Aerospace Society, 2022.

This source describes Open Hardware that is licensed under CERN-OHL-S v2, or any later version.

You may redistribute and modify this source and make products using it under the terms of the CERN-OHL-S v2 (https://ohwr.org/cern_ohl_s_v2.txt).

This source is distributed WITHOUT ANY EXPRESS OR IMPLIED WARRANTY, INCLUDING OF MERCHANTABILITY, SATISFACTORY QUALITY AND FITNESS FOR A PARTICULAR PURPOSE. Please see the CERN-OHL-S v2 for applicable conditions.

Source location: https://github.com/oresat/

If you require a different license for this open hardware project, please contact us at [oresat@pdx.edu](mailto:oresat@pdx.edu).
