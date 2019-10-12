Author: Andrey Albershteyn
Date: 28.07.19
Status: Good Enough
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

**[29.07.19]**

According to this [1] using relay we get unwanted electromagnetic radiation
which is can be a problem for Bluetooth. I don't think it will broke it
completely but can decrease distance and quality of signal. The most of the
advantages of the relay doesn't suite for this application (such as AC
switching, isolation, robustness)

Mosfet is small and cheap and looks like it can be used as a switch. So, I don't
see why not use for this project.

I decided to you P-MOSFET. AOD4185L MOSFET P Trench 40V 40A 3V @ 250uA 15 mΩ @
20A,10V TO-252-2(DPAK) RoHS

Proof that it is used as reverse polarity [2]

### References

[1]: https://electronics.stackexchange.com/questions/10092/relay-vs-transistor
[2]: https://electronics.stackexchange.com/questions/61692/reverse-polarity-protection
