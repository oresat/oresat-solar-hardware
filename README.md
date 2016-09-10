# Solar
OreSat solar array designs and CAD.

# Overview

The solar array provides operating power and charges Oresat's lipo bank.

<p align="center">
  <img src="http://i.imgur.com/sdlSdFT.png"/>
</p>
[Block Diagram](http://i.imgur.com/8L8mwpQ.png)

The Solar Array will utilize gallium arsenide solar cell's.  We are considering using cells manufactured by [Alta Devices](https://http://www.altadevices.com/).  The SPV1040 switching boost regulator will condition the incoming power.  The LTC2990 sense IC will communicate via I2C with the system controller.  A pair of mosfets are connected to a shorting bar that will keep the cubesat off until it is launched.

# Design

- [Current Design Docs](https://docs.google.com/document/d/12vTM7Nvca8MzUQj_UqHETxqTQUYI2aZk1vTmDey_-34/edit?usp=sharing) on Google Docs.
- [Parts Selection](https://github.com/oresat/solar/blob/master/Parts_Selection.md)
- [Bill of Materials](https://github.com/oresat/solar/blob/master/doc/BOM/Rev1_BOM.ods)
- [Eagle Schematic](https://github.com/oresat/solar/blob/master/eagle/1u_panel.sch)
- [Eagle Layout](https://github.com/oresat/solar/blob/master/eagle/1u_panel.brd)

# Contents
- doc
  - BOM - Bill of Materials
  - PDF - Drawings (schematics, board layout etc.)
  - Solar Cells - Info on cells
  - datasheets - Datasheets for ic's
- eagle - Drawings and libs for eagle
  - lib - Project specific parts lib
- kicad - Outdated versions done on kicad (do not use)
- mechanical - CAD drawings of physical board


## Project Team
  [Andrew Greenberg](https://github.com/andrewgreenberg)  
  [Austin Joseph](https://github.com/austinjoseph)



