# Build automation for KiCad projects
#
# The makefile automatically looks for a local *.kicad_pro file and assumes that's your project name. It
# then assumes you want your build products to go into a build folder (you do, trust us).
#
# PRESET_NAME is the preset for your BOM format. kicad-cli will happily output a completely useless BOM
# of just REF, VALUE, FOOTPRINT, that's it, unless you set up the BOM tool with a "preset".
# We set up bom-preset when working in KiCad which has all the things when you're editing the schematic,
# and then use bom-output-preset when generating a CSV file to get rid of value, footprint, and datasheet.

PROJECT_FILE = $(firstword $(shell echo *.kicad_pro))
PROJECT_NAME = $(PROJECT_FILE:%.kicad_pro=%)
SCHEMATIC    = $(PROJECT_NAME).kicad_sch
BOARD        = $(PROJECT_NAME).kicad_pcb
OUTPUT_DIR  ?= build
PRESET_NAME  = bom-export-preset

# Default target (first target is default)
all: bom ipc gerber drill pos step

# Generate build files
bom:	## Generate a CSV Bill of Materials (BOM) with the output preset file that you created in your schematic.
	kicad-cli sch export bom --preset $(PRESET_NAME) -o $(OUTPUT_DIR)/$(PROJECT_NAME).csv $(SCHEMATIC)
	
ipc:	## IPC-2581 is an open standard used for board fab and assembly
	kicad-cli pcb export ipc2581 -o $(OUTPUT_DIR)/$(PROJECT_NAME)-ipc.xml $(BOARD)
	
gerber:	## Modern Gerber files for all the standard layers (kill the jobs file)
	kicad-cli pcb export gerbers -o $(OUTPUT_DIR) --board-plot-params $(BOARD)
	rm -f $(OUTPUT_DIR)/*.gbrjob
	
drill:	## Excellon drill files, separated by plated / non-plated holes which is sometimes useful
	kicad-cli pcb export drill -o $(OUTPUT_DIR) --excellon-separate-th $(BOARD)
	
pos:	## Position files for pick and place machines (also in the ipc file) 
	kicad-cli pcb export pos -o $(OUTPUT_DIR)/$(PROJECT_NAME).pos --exclude-dnp $(BOARD)
	
step:	## A 3D STEP file to import into your MCAD package
	kicad-cli pcb export step -o $(OUTPUT_DIR)/$(PROJECT_NAME).step $(BOARD)
	
clean:	## delete everything for clean
	rm -f $(OUTPUT_DIR)/*

# Tell make that these are commands, not files
.PHONY: all bom ipc gerber drill pos step clean
