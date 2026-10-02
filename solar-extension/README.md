---
title: "**OreSat Solar Extension Board**"
subtitle: |
  **Fabrication and Assembly Information**\
  For build 2026-06-23T21-24-18
fontsize: 10pt
geometry:
  - margin=0.5in
toc: true
toc-depth: 2
colorlinks: true
urlcolor: blue
---

\newpage

# About this Board

## Board Description

This board connects the Oresat Solar Simulator to an OreSat engineering or development unit (specifically the End or Mid Cards). It allows us to plug HIL-run solar modules right into the engineering unit.

## Documentation Links

- Git repository: <https://github.com/oresat/oresat-solar-hardware>
- **TODO:** Design Notes + Design Review Notes

## Documentation Files

| Filename                        | Notes                                    |
| ------------------------------- | ---------------------------------------- |
| README.pdf                      | This README file                         |
| flatsat-breakout-outline.dxf        | Board outline (with holes) in DXF format |
| flatsat-breakout-pcba.step          | 3D model of PCBA (with components)       |
| flatsat-breakout-render-bot.jpg     | Render of the top of the 3D model        |
| flatsat-breakout-render-bot.jpg     | Render of the bottom of the 3D model     |
| flatsat-breakout-schematic.pdf      | PDF of board schematics                  |

## Contact Information

- Website: <https://www.oresat.org/>
- Email: <oresat@pdx.edu>
- Instagram: @pdxaerospace

## Board Renders

![Render of the top of the 3D model](./build/documentation/flatsat-breakout-render-top.jpg){width=50%}
![Render of the bottom of the 3D model](./build/documentation/flatsat-breakout-render-bot.jpg){width=50%}

\newpage

# Printed Circuit Board (PCB) Fabrication Information

## Board Info

- 2 layer board
- Bounding box is TBD
- Board thickness is 1.59 mm

## Board Requirements

- Design Rules
    - Minimum Trace / Space design rules
       - Outer layers: 0.127 mm (5.0 mil) / 0.127 mm (5.0 mil)
       - Inner layers: 0.127 mm (5.0 mil) / 0.127 mm (5.0 mil)
    - Outer dimension router tolerance: +/- 0.254 mm (10.0 mil)
    - Hole placement tolerance: +/- 0.075 mm (3.0 mil)
    - Inner tab routed slot tolerance: +/- 0.254 mm (10.0 mil)
- Drills
   - Drill Positional Tolerance: 0.051 mm (2.0 mil)
   - Drill Size tolerance: +/- 0.064 mm (2.5 mil)
- Plated/Un-plated holes
  - Via/PTH minimum diameter: 0.254 mm (10 mil)
  - Via/PTH minimum annulus: 0.102 mm (4 mil) radius
- Outline/Routing
  - No requirements
- Slots
  - There are no slots.
- Cutouts
  - There are no cutouts
- There are 3 fiducials on the top layer.
- Panel tabs ("mouse bites")
   - Card edges must be smooth; no mouse bites or other intrusions into the card outline.
   - If external mouse bites are required, minimize and customer will remove by hand before assembly.
- If not otherwise specified, build to IPC 6012 Class 2 or better.

## Stackup /  Materials

- Outside copper layers is 1 oz Cu after plating (0.043 mm / 1.7 mil)
- Inside copper layers are 0.5 oz Cu (0.018 mm / 0.7 mil)
- There are no requirements on the prepreg or core of this four layer stackup.
- Board Surface treatment should be ENIG, althogh immersion Silver is acceptable.
- White silkscreen on top and bottom surface
- Taiyo PSR-4000 or equivalent soldermask on top and bottom, no requirements for color.

## Array / Panel Information

- Coordinate with Contract Manufacturer (CM) for optimal size of this panel.
- If no feedback from CM, then produce single boards (no panel).

## Fabrication Files

### IPC-2581 File

| Filename                 | Notes                                   |
| ------------------------ | --------------------------------------- |
| flatsat-breakout-ipc2581.xml | IPC-2581 board information file         |

### Legacy PCB Files

| Filename                      | Notes                                         |
| ------------------------------| --------------------------------------------- |
| flatsat-breakout-Edge_Cuts.gbr    | RS274X file for the dimension (outline) layer |
| flatsat-breakout-F_Silkscreen.gbr | RS274X file for the top silkscreen            |
| flatsat-breakout-F_Mask.gbr       | RS274X file for the top soldermask            |
| flatsat-breakout-F_Cu.gbr         | RS274X file for the top copper layer          |
| flatsat-breakout-In1_Cu.gbr       | RS274X file for the layer 2 copper            |
| flatsat-breakout-In2_Cu.gbr       | RS274X file for the layer 3 copper            |
| flatsat-breakout-B_Cu.gbr         | RS274X file for the bottom copper layer       |
| flatsat-breakout-B_Mask.gbr       | RS274X file for the bottom soldermask         |
| flatsat-breakout-B_Silkscreen.gbr | RS274X file for the bottom silkscreen         |
| flatsat-breakout-NPTH.drl         | Excellon file for non-plated through holes    |
| flatsat-breakout-PTH.drl          | Excellon file for plated through holes        | 

\newpage

# Printed Circuit Board Assembly (PCBA) Information

## Assembly Info

- This PCBA uses both surface mount (SMT) and through-hole (THT) components.

## Assembly Requirements

- Assemble to IPC Class 2 or better
- Bake components that are not moisture sealed to appropriate levels as required.
- Any solder paste (leaded or RoHS) is acceptable. RoHS solder is slightly preferred.
- Any no-clean or aqueous wash flux is acceptable.
- No conformal coating.

## Component Specific Assembly Information

- No specific information

## Assembly Files

### IPC-2581 File

| Filename                 | Notes                           |
| ------------------------ | ------------------------------- |
| flatsat-breakout-ipc2581.xml | IPC-2581 board information file |

### Bill of Materials (BOM)

| Filename             | Description                            |
| -------------------- | -------------------------------------- |
| flatsat-breakout-bom.csv | BOM in Comma Separated Variable format |

### Solder Paste Stencils

| Filename                 | Notes                                            |
| ------------------------ | ------------------------------------------------ |
| flatsat-breakout-B_Paste.gbr | RS274X file for top/front solder paste stencil   |
| flatsat-breakout-F_Paste.gbr | RS274X file for bottom/back solder paste stencil |

### Mounting/Placement Location

| Filename            | Description                                 |
| ------------------- | ------------------------------------------- |
| flatsat-breakout.pos | Pick and place locations for components     |

