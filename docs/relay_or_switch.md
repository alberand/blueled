Author: Andrey Albershteyn
Date: 28.07.19
Status: Open
Tags: feature, circuit-power-off

### Brief 

How to power off the whole device? With switch, relay or something else?

### Timeline - Analysis & Solution

**[28.07.19]**

I want to completely power off the circuit as I assume it more safe. No current
no problems. The following factors play role:

    * Humidity can create short circuit
    * High environment temperature + overheat on the output terminal
    * Low quality of Chinese components
    * Bug in the software (not fully disable led strip)
    * etc????

**[28.07.19]**

I find a few way how to power off the circuit:

    * Switch
    * Relay
    * MOSFET

**Switch** - very simple and cheap solution. However, the current in the circuit
is 5A. Therefore, I need some reliable high current switch. Unfortunately, all
of them are quite big for such a small device.

**Relay** - small, cheap, in combination with a small switch will give the same
functionality. The disadvantage is the *cwak* noise.

**MOSFET** - requires radiator which quite big.
