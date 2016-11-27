# OreSat Solar Modules

This repo contains several designs for [OreSat's](oresat.org) solar array. The arrays are based on [Alta Devices](https://http://www.altadevices.com/) GaAs 5 cell solar modules, which produce about 1 W in AM0 (space) conditions. Part of OreSat's design is a module bus system that spans 1 - 3 U, so each array is its own 1U "panel". OreSat is 2U, so we have 2 of these modules per side. This approach has pretty severe drawbacks in terms of solar cell coverage area, but it's extremely flexible as our plans, and thus power needs, change. 

![CAD drawings of the satellite and panels](https://github.com/oresat/solar/blob/master/images/oresat-solar-modules.png)

# Rev 0 Design

So our first design is based on a SPV1040 Maximum Power Point Tracker (MPPT) IC, an STM32F0 processor because CAN-based telemetry, and an LTC2990 sense IC (V, I and T) because that chip does everything. A pair of MOSFETs connect to our "system shutdown" signal that keeps the cubesat powered off until deployment.

- [Current Design Docs](https://docs.google.com/document/d/12vTM7Nvca8MzUQj_UqHETxqTQUYI2aZk1vTmDey_-34/edit?usp=sharing) - Currently on Google Docs, sorry.
- [Parts Selection](https://github.com/oresat/solar/blob/master/Parts_Selection.md) - incomplete, see google docs above for now.
- [Bill of Materials](https://github.com/oresat/solar/blob/master/doc/BOM/Rev1_BOM.ods)
- [PDF Schematic](https://github.com/oresat/solar/blob/master/drawings/1u_panel_schematic.pdf)
- CAD files
   - [Eagle Schematic](https://github.com/oresat/solar/blob/master/eagle/1u_panel.sch)
   - [Eagle Layout](https://github.com/oresat/solar/blob/master/eagle/1u_panel.brd)
   - [STEP file 3D model](https://github.com/oresat/solar/blob/master/drawings/solar-module.step)

# File Structure

- doc
  - BOM - Bill of Materials
  - PDF - Drawings (schematics, board layout etc.)
  - Solar Cells - Info on cells
  - datasheets - Datasheets for ic's
- eagle - Drawings and libs for eagle
  - lib - Project specific EAGLE libraries
- kicad - Outdated versions done on kicad (do not use)
- drawings - CAD drawings of physical board, etc.
- images - PNGs for the readme

# Rev 1 Design

Shhhh! Don't tell anyone: rev 1 is a super secret project that uses a  **Zeta converter** running the *Incremental Conductance algorithm* on a 32bit ARM microcontroller that talks CAN! Oh, it's going to be great. After we figure out how to make it not catch fire in space, of course. It's all preliminary, but you can find it in the [MPPT folder](https://github.com/oresat/solar/tree/master/MPPT).

## Project Team
  [Andrew Greenberg](https://github.com/andrewgreenberg)  
  [Austin Joseph](https://github.com/austinjoseph)



