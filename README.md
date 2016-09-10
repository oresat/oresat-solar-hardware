# Solar
OreSat solar array designs and CAD.

Current design documentation can be found [here on the solar array google doc](https://docs.google.com/document/d/12vTM7Nvca8MzUQj_UqHETxqTQUYI2aZk1vTmDey_-34/edit?usp=sharing). Just ask if you need editing permissions.

# Overview

The solar array provides operating power and charges Oresat's lipo bank.

<p align="center">
  <img src="http://i.imgur.com/8L8mwpQ.png"/>
</p>
[Block Diagram](http://i.imgur.com/8L8mwpQ.png)

The Solar Array will utilize gallium arsenide solar cell's.  We are considering using cells manufactured by [Alta Devices](https://http://www.altadevices.com/).  The SPV1040 switching boost regulator will condition the incoming power.  The LTC2990 sense IC will communicate via I2C with the system controller.  A pair of mosfets are connected to a shorting bar that will keep the cubesat off until it is launched.

# Design
[Parts Selection]
[Bill of Materials]
[Eagle Schematic](https://github.com/oresat/solar/blob/master/eagle/1u_panel.sch)
[Eagle Layout](https://github.com/oresat/solar/blob/master/eagle/1u_panel.brd)



