# OreSat Solar Modules

This repo contains several designs for [OreSat's](oresat.org) solar array. The arrays are based on [Alta Devices](https://http://www.altadevices.com/) GaAs 5 cell solar modules, which produce about 1 W in AM0 (space) conditions. Part of OreSat's design is a module bus system that spans 1 - 3 U, so each array is its own 1U "panel". OreSat is 2U, so we have 2 of these modules per side. This approach has pretty severe drawbacks in terms of solar cell coverage area, but it's extremely flexible as our plans, and thus power needs, change. 

![CAD drawings of the satellite and panels](https://github.com/oresat/solar/blob/master/images/oresat-solar-modules.png)

# Rev 1 Design: "1u_panel"

Our first design is based on a SPV1040 Maximum Power Point Tracker (MPPT) IC, an STM32F0 processor because CAN-based telemetry, and an LTC2990 sense IC (V, I and T) because that chip does everything. A pair of MOSFETs connect to our "system shutdown" signal that keeps the cubesat powered off until deployment. You can find all of the design and CAD files in the ['1u_panel' folder](https://github.com/oresat/solar/tree/master/1u_panel).

# Next generation design: "zeta"

Our next super secret project (open source, of course) uses a  *Zeta converter* running the *Incremental Conductance algorithm* on a 32bit ARM microcontroller that talks CAN! Oh, it's going to be great. After we figure out how to make it not catch fire in space, of course. It's all preliminary, but you can find it in the ['zeta' folder](https://github.com/oresat/solar/tree/master/zeta).

## Project Team (so far!)

- [Andrew Greenberg](https://github.com/andrewgreenberg)  
- [Austin Joseph](https://github.com/austinjoseph)



