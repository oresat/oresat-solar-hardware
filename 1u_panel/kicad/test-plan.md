# 1U Panel Test Plan

This assumes a completely assembled board, with a detailed visual inspection done that removes all visible shorts and corrects for any visually bad solder joints.

This testing assumes R24-R27 (CAN bus addresses) are not stuffed.


## Equipment

- Two channel power supply with constant current limit
- DMM
- Scope (50 MHz or better)
- SWD programmer for the STM32F091 (a debug cable, a Card Debug Board v2, and a laptop that can compile and program OreSat firmware).
- Two solar cell test panel with halogen bulb (or solar simulator).
- OreSat battery card (or any 2S Li ion battery pack) that is around 7.2 V, and definitely between 6.0 V and < 8.0 V.
- JouleScope with JouleScope software
- Temperature controlled hot air gun.

## Test Plan

In the following tests, do not continue to test if a test fails. Instead, debug the PCB then continue to test. If you don't fix these problems in order, you may end up destroying other circuits.
1. Circuit Test: Power
   1. Set: 5V @ 50 mA max into `Vsolar`.
   1. Measure: power supply is providing no more than 20 mA (TODO: MEASURED VALUE).
      - Debugging notes: It's not a big deal if it's near 20mA, but if the current draw is 50 mA, you have a short. Removing R17, R14, and R20 will let you identify where the short is. Hunt down the short in the downstream circuits using these three resistors.
   1.Measure: 4.7V +/- 0.1V at `TP12`.
      - Debugging: The LT1618 should be off, so you'll just see the drop of D5. The LTC4412 may not work at 5V, so it's OK if `TP14` is weird.
   1. Measure: 3.3V +/- 5% at `TP6`. (TODO: ACTUAL PERCENTAGE ERROR)
      - That TPS63030 is notoriously hard to reflow, so if that's not working, probably reflow that IC or pull it and retry.
   1. Set: insert RBF jumper into J1.
   1. Measure: `TP6` should drop to near 0 V.
      * Debugging notes: This verifies the !SD circuit is working on the 3.3V supply.
   1. Set: Remove RBF jumper.
   1. Set: Pull `TP10` up to 3.3V @ 10 mA max.
   1. Measure: 8.2V +1%/-10% at `TP12`.
      * Debugging notes: The current limit on the LT1618 is set to very low, so it might current limit if there's any issue down the line towards Vbus.
   1. Measure: 8.4 V +1%/-10% at `TP14`.
   1. Set: insert RBF jumper into J1.
   1. Measure: ~ 0 V on `TP14`.
      * Debugging notes: This verifies the !SD circuit is working on MPPT / 8.2V supply.
   1. Set: Remove RBF jumper.
   1. Set: remove power from `TP10`. 
   
2. Program microcontroller
   1. Set: 5V @ 50 mA max into `Vsolar`.
   1. Set: Make sure UART debugging is enable in firmware (TODO: HOW?!)
   1. Set: Program microcontroller using the SWD programmer.
      * Debugging Notes: make sure to do `make clean && make all` at least once before `make write`.
   1. Measure: LED D6 should be blinking.
   1. Measure: Reboot the microcontroller using the reset switch on the Card Debug board and look for serial console boot up message.

3. Functional Test: MPPT
   1. Set: hookup two cell test panel to `Vsolar`.
   1. Set: Turn on some amount of irradiance on the cell test panel to give it plenty of power to run, like 25% of 1 sun.
   1. Set: hook up battery pack to `Vbus` (or `TP14`) through JouleScope and run JouleScope software.
   1. Measure: some amount of power flowing into the battery pack when irradiance is reasonable.
   1. Set: Make irradiance go up and down.
   1. Measure: see amount of power flowing into the battery pack track the irradiance level.

3. Functional Test: Temperature
   1. Set: same setup as in (3) above.
   1. Measure: on serial debug output, temperature on both TMP101A is around room temperature (~ 25 C).
   1. Set: Adjust hot air gun down to ~ 100 C and apply hot air to each TMP101A.
   1. Measure: see the temperature on each TMP101A go up to ~ 100 C.

   
   
   
   
