EESchema Schematic File Version 4
LIBS:blueled-cache
EELAYER 30 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title ""
Date ""
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L MCU_Microchip_ATmega:ATmega328P-AU U1
U 1 1 5CAE668A
P 5300 3450
F 0 "U1" H 5300 1861 50  0000 C CNN
F 1 "ATmega328P-AU" H 5300 1770 50  0000 C CNN
F 2 "Package_QFP:TQFP-32_7x7mm_P0.8mm" H 5300 3450 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 5300 3450 50  0001 C CNN
	1    5300 3450
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C1
U 1 1 5CAF8DD1
P 2700 3600
F 0 "C1" H 2815 3646 50  0000 L CNN
F 1 "10uF" H 2815 3555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2700 3600 50  0001 C CNN
F 3 "~" H 2700 3600 50  0001 C CNN
	1    2700 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:CP1 C2
U 1 1 5CAFA462
P 3700 3600
F 0 "C2" H 3815 3646 50  0000 L CNN
F 1 "10uF" H 3815 3555 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 3700 3600 50  0001 C CNN
F 3 "~" H 3700 3600 50  0001 C CNN
	1    3700 3600
	1    0    0    -1  
$EndComp
Wire Wire Line
	2700 3450 2950 3450
$Comp
L power:GND #PWR0101
U 1 1 5CAFFAEC
P 3250 4100
F 0 "#PWR0101" H 3250 3850 50  0001 C CNN
F 1 "GND" H 3255 3927 50  0000 C CNN
F 2 "" H 3250 4100 50  0001 C CNN
F 3 "" H 3250 4100 50  0001 C CNN
	1    3250 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	3250 3750 3250 3850
Wire Wire Line
	2450 3450 2700 3450
Connection ~ 2700 3450
Wire Wire Line
	2700 3750 2700 3850
Wire Wire Line
	2700 3850 3250 3850
Connection ~ 3250 3850
Wire Wire Line
	3700 3750 3700 3850
Wire Wire Line
	3250 3850 3700 3850
Text GLabel 4250 3450 2    50   Input ~ 0
+3V3
$Comp
L power:GND #PWR0102
U 1 1 5CB7FE99
P 9000 4300
F 0 "#PWR0102" H 9000 4050 50  0001 C CNN
F 1 "GND" H 9005 4127 50  0000 C CNN
F 2 "" H 9000 4300 50  0001 C CNN
F 3 "" H 9000 4300 50  0001 C CNN
	1    9000 4300
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0103
U 1 1 5CB803CB
P 5300 5350
F 0 "#PWR0103" H 5300 5100 50  0001 C CNN
F 1 "GND" H 5305 5177 50  0000 C CNN
F 2 "" H 5300 5350 50  0001 C CNN
F 3 "" H 5300 5350 50  0001 C CNN
	1    5300 5350
	1    0    0    -1  
$EndComp
Wire Wire Line
	10500 4300 9800 4300
Connection ~ 9800 4300
Connection ~ 9000 4300
Wire Wire Line
	9800 4050 9800 4300
Wire Wire Line
	9800 4300 9000 4300
Wire Wire Line
	9000 4050 9000 4300
Wire Wire Line
	8300 4300 9000 4300
$Comp
L Regulator_Linear:LM1117-3.3 U3
U 1 1 5CB83042
P 3250 3450
F 0 "U3" H 3250 3692 50  0000 C CNN
F 1 "LM1117-3.3" H 3250 3601 50  0000 C CNN
F 2 "smd-semi:SOT-223" H 3250 3450 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm1117.pdf" H 3250 3450 50  0001 C CNN
	1    3250 3450
	1    0    0    -1  
$EndComp
Text GLabel 5300 1650 1    50   Input ~ 0
+3V3
Wire Wire Line
	5300 1650 5300 1850
$Comp
L power:GND #PWR0104
U 1 1 5CBB96C3
P 7250 3200
F 0 "#PWR0104" H 7250 2950 50  0001 C CNN
F 1 "GND" H 7255 3027 50  0000 C CNN
F 2 "" H 7250 3200 50  0001 C CNN
F 3 "" H 7250 3200 50  0001 C CNN
	1    7250 3200
	1    0    0    -1  
$EndComp
$Comp
L pasv-xtal:RESON-MURATA-CSTCE X1
U 1 1 5CBDC71D
P 7000 2850
F 0 "X1" H 7078 2804 50  0000 L CNN
F 1 "RESON-MURATA-CSTCE" H 7078 2895 50  0000 L CNN
F 2 "manuf:MURATA_CSTCE" H 7000 2700 60  0001 C CNN
F 3 "" H 7000 2850 60  0000 C CNN
	1    7000 2850
	-1   0    0    1   
$EndComp
Wire Wire Line
	5900 2950 7000 2950
Wire Wire Line
	7100 2850 7250 2850
Wire Wire Line
	7250 2850 7250 3200
Wire Wire Line
	6800 2750 6800 2850
Wire Wire Line
	6800 2850 5900 2850
$Comp
L Device:R_Small R1
U 1 1 5CBE0D3A
P 6350 3600
F 0 "R1" H 6409 3646 50  0000 L CNN
F 1 "1k" H 6409 3555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 6350 3600 50  0001 C CNN
F 3 "~" H 6350 3600 50  0001 C CNN
	1    6350 3600
	1    0    0    -1  
$EndComp
Text GLabel 6350 3350 1    50   Input ~ 0
+3V3
Wire Wire Line
	5300 1850 5400 1850
Wire Wire Line
	5400 1850 5400 1950
Connection ~ 5300 1850
Wire Wire Line
	5300 1850 5300 1950
Text GLabel 6150 3950 2    50   Input ~ 0
RX
Text GLabel 6150 4050 2    50   Input ~ 0
TX
Wire Wire Line
	5900 3950 6150 3950
Text GLabel 7600 2450 0    50   Input ~ 0
RX
Text GLabel 8150 2550 0    50   Input ~ 0
TX
Wire Wire Line
	8300 2550 8150 2550
Text GLabel 8150 3550 0    50   Input ~ 0
+3V3
Wire Wire Line
	8150 3550 8300 3550
$Comp
L power:GND #PWR0105
U 1 1 5CBEBE63
P 7450 3750
F 0 "#PWR0105" H 7450 3500 50  0001 C CNN
F 1 "GND" H 7455 3577 50  0000 C CNN
F 2 "" H 7450 3750 50  0001 C CNN
F 3 "" H 7450 3750 50  0001 C CNN
	1    7450 3750
	1    0    0    -1  
$EndComp
$Comp
L Device:C C3
U 1 1 5CBEE490
P 4250 2400
F 0 "C3" H 4365 2446 50  0000 L CNN
F 1 "0.1u" H 4365 2355 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4288 2250 50  0001 C CNN
F 3 "~" H 4250 2400 50  0001 C CNN
	1    4250 2400
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2250 4700 2250
$Comp
L power:GND #PWR0106
U 1 1 5CBEF7A5
P 4250 2750
F 0 "#PWR0106" H 4250 2500 50  0001 C CNN
F 1 "GND" H 4255 2577 50  0000 C CNN
F 2 "" H 4250 2750 50  0001 C CNN
F 3 "" H 4250 2750 50  0001 C CNN
	1    4250 2750
	1    0    0    -1  
$EndComp
Wire Wire Line
	4250 2750 4250 2550
Wire Wire Line
	6350 3350 6350 3500
Wire Wire Line
	6350 3700 6350 3750
$Comp
L Device:R_Small R2
U 1 1 5CBF3B20
P 4150 3600
F 0 "R2" H 4209 3646 50  0000 L CNN
F 1 "1k" H 4209 3555 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4150 3600 50  0001 C CNN
F 3 "~" H 4150 3600 50  0001 C CNN
	1    4150 3600
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5CBF4695
P 4150 3900
F 0 "D1" V 4189 3783 50  0000 R CNN
F 1 "LED" V 4098 3783 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4150 3900 50  0001 C CNN
F 3 "~" H 4150 3900 50  0001 C CNN
	1    4150 3900
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4150 3700 4150 3750
Wire Wire Line
	3700 3450 4150 3450
Wire Wire Line
	4150 3500 4150 3450
Connection ~ 4150 3450
Wire Wire Line
	4150 3450 4250 3450
Text Label 1200 4450 0    50   ~ 0
GND
$Comp
L power:GND #PWR0109
U 1 1 5CC59A0A
P 1200 4450
F 0 "#PWR0109" H 1200 4200 50  0001 C CNN
F 1 "GND" H 1205 4277 50  0000 C CNN
F 2 "" H 1200 4450 50  0001 C CNN
F 3 "" H 1200 4450 50  0001 C CNN
	1    1200 4450
	1    0    0    -1  
$EndComp
Text Label 2500 3450 0    50   ~ 0
VIN
Text Label 3900 3450 0    50   ~ 0
+3V3
Text Label 7250 3050 0    50   ~ 0
GND
Text Label 9050 4300 0    50   ~ 0
GND
Text Label 8150 3550 0    50   ~ 0
+3V3
Text Label 5300 1750 0    50   ~ 0
+3V3
Text Label 4250 2650 0    50   ~ 0
GND
Text Label 4200 4800 0    50   ~ 0
DATA
Text GLabel 6150 4650 2    50   Input ~ 0
DATA
$Comp
L Connector:Screw_Terminal_01x03 J2
U 1 1 5CC5BA14
P 4000 4800
F 0 "J2" H 4080 4842 50  0000 L CNN
F 1 "Screw_Terminal_01x03" H 4080 4751 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-3_P5.08mm" H 4000 4800 50  0001 C CNN
F 3 "~" H 4000 4800 50  0001 C CNN
	1    4000 4800
	-1   0    0    -1  
$EndComp
NoConn ~ 5900 3650
NoConn ~ 5900 3550
NoConn ~ 5900 3450
NoConn ~ 5900 3350
NoConn ~ 5900 3250
NoConn ~ 5900 3150
NoConn ~ 8300 2650
NoConn ~ 8300 2750
NoConn ~ 8300 2850
NoConn ~ 8300 2950
NoConn ~ 8300 3050
NoConn ~ 8300 3150
NoConn ~ 8300 3250
NoConn ~ 8300 3350
NoConn ~ 10500 2550
NoConn ~ 10500 2750
NoConn ~ 10500 2850
NoConn ~ 10500 2950
NoConn ~ 10500 3050
NoConn ~ 10500 3150
NoConn ~ 10500 3250
NoConn ~ 10500 3350
Text Label 6450 3750 0    50   ~ 0
RESET
Text Label 8300 3450 2    50   ~ 0
HC-RESET
Text GLabel 6150 4350 2    50   Input ~ 0
HC-RESET
Text GLabel 7850 3450 0    50   Input ~ 0
HC-RESET
Wire Wire Line
	7850 3450 8300 3450
NoConn ~ 9100 4050
NoConn ~ 9200 4050
NoConn ~ 9300 4050
NoConn ~ 9500 4050
NoConn ~ 9600 4050
NoConn ~ 9700 4050
Text Label 7200 3750 0    50   ~ 0
RESET_GND
Wire Wire Line
	6350 3750 6800 3750
Wire Wire Line
	6800 2750 7000 2750
NoConn ~ 4700 2450
NoConn ~ 4700 2550
$Comp
L Connector:Barrel_Jack J1
U 1 1 5CDBC439
P 900 4350
F 0 "J1" H 957 4675 50  0000 C CNN
F 1 "Barrel_Jack" H 957 4584 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_CUI_PJ-102AH_Horizontal" H 950 4310 50  0001 C CNN
F 3 "~" H 950 4310 50  0001 C CNN
	1    900  4350
	1    0    0    -1  
$EndComp
Text GLabel 4400 4800 2    50   Input ~ 0
DATA
Wire Wire Line
	4200 4800 4400 4800
Wire Wire Line
	5300 4950 5300 5350
$Comp
L power:GND #PWR0107
U 1 1 5CBF586D
P 4150 4100
F 0 "#PWR0107" H 4150 3850 50  0001 C CNN
F 1 "GND" H 4155 3927 50  0000 C CNN
F 2 "" H 4150 4100 50  0001 C CNN
F 3 "" H 4150 4100 50  0001 C CNN
	1    4150 4100
	1    0    0    -1  
$EndComp
Wire Wire Line
	4150 4050 4150 4100
Wire Wire Line
	3250 3850 3250 4100
Text Notes 7350 7500 0    50   ~ 0
Bluetooth Ledstrip controller
Text Notes 8150 7650 0    50   ~ 0
14/05/2019
Text Notes 8200 7750 0    50   ~ 0
alberand
$Comp
L Connector_Generic:Conn_02x03_Top_Bottom J3
U 1 1 5D06C568
P 7000 5050
F 0 "J3" H 7050 5367 50  0000 C CNN
F 1 "ICSP" H 7050 5276 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_1x06_P2.54mm_Vertical" H 7000 5050 50  0001 C CNN
F 3 "~" H 7000 5050 50  0001 C CNN
	1    7000 5050
	1    0    0    -1  
$EndComp
Text GLabel 6550 5150 0    50   Input ~ 0
RESET
Text GLabel 7500 4950 2    50   Input ~ 0
+3V3
Wire Wire Line
	7500 4950 7300 4950
Text GLabel 7500 5050 2    50   Input ~ 0
MOSI
Text GLabel 6550 4950 0    50   Input ~ 0
MISO
Text GLabel 6550 5050 0    50   Input ~ 0
SCK
Wire Wire Line
	6550 5050 6800 5050
Wire Wire Line
	6550 4950 6800 4950
Wire Wire Line
	7300 5050 7500 5050
$Comp
L power:GND #PWR01
U 1 1 5D07BC0F
P 7350 5250
F 0 "#PWR01" H 7350 5000 50  0001 C CNN
F 1 "GND" H 7355 5077 50  0000 C CNN
F 2 "" H 7350 5250 50  0001 C CNN
F 3 "" H 7350 5250 50  0001 C CNN
	1    7350 5250
	1    0    0    -1  
$EndComp
Wire Wire Line
	7300 5150 7350 5150
Wire Wire Line
	7350 5150 7350 5250
Text Label 6550 5150 0    50   ~ 0
RESET
Wire Wire Line
	6550 5150 6800 5150
Text GLabel 6050 2650 2    50   Input ~ 0
MISO
Text GLabel 6050 2550 2    50   Input ~ 0
MOSI
Text GLabel 6050 2750 2    50   Input ~ 0
SCK
Wire Wire Line
	5900 2550 6050 2550
Wire Wire Line
	5900 2650 6050 2650
Wire Wire Line
	5900 2750 6050 2750
$Comp
L Device:R_Small R3
U 1 1 5D089425
P 7750 2250
F 0 "R3" H 7809 2296 50  0000 L CNN
F 1 "1k" H 7809 2205 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7750 2250 50  0001 C CNN
F 3 "~" H 7750 2250 50  0001 C CNN
	1    7750 2250
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D2
U 1 1 5D08942B
P 7750 1950
F 0 "D2" V 7789 1833 50  0000 R CNN
F 1 "LED" V 7698 1833 50  0000 R CNN
F 2 "LED_SMD:LED_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 7750 1950 50  0001 C CNN
F 3 "~" H 7750 1950 50  0001 C CNN
	1    7750 1950
	0    -1   -1   0   
$EndComp
Wire Wire Line
	7600 2450 7750 2450
Text GLabel 7700 1750 0    50   Input ~ 0
+3V3
Wire Wire Line
	7750 2100 7750 2150
Wire Wire Line
	7750 2350 7750 2450
Connection ~ 7750 2450
Wire Wire Line
	7750 2450 8300 2450
Wire Wire Line
	7700 1750 7750 1750
Wire Wire Line
	7750 1750 7750 1800
Text GLabel 10600 3550 2    50   Input ~ 0
HC-DISCNCT
Text GLabel 10650 2650 2    50   Input ~ 0
HC-STATE
Wire Wire Line
	10500 3550 10600 3550
Text GLabel 6150 4150 2    50   Input ~ 0
HC-STATE
Text GLabel 6150 4450 2    50   Input ~ 0
HC-DISCNCT
Wire Wire Line
	6150 4050 5900 4050
Wire Wire Line
	5900 4350 6150 4350
Wire Wire Line
	5900 4450 6150 4450
Wire Wire Line
	5900 4150 6150 4150
Text GLabel 10650 2450 2    50   Input ~ 0
HC-ATMODE
Wire Wire Line
	10500 2450 10650 2450
Text GLabel 6150 4250 2    50   Input ~ 0
HC-ATMODE
Wire Wire Line
	5900 4650 6150 4650
Wire Wire Line
	5900 4250 6150 4250
NoConn ~ 5900 4550
$Comp
L Device:Q_PMOS_SDG Q1
U 1 1 5D461D8C
P 2200 4550
F 0 "Q1" H 2406 4596 50  0000 L CNN
F 1 "Q_PMOS_SDG" H 2406 4505 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:TO-252-3_TabPin4" H 2400 4650 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Alpha-Omega-Semicon-AOS-AOD4185_C77993.pdf" H 2200 4550 50  0001 C CNN
	1    2200 4550
	1    0    0    -1  
$EndComp
Wire Wire Line
	2300 4750 2300 4800
Wire Wire Line
	2300 4800 2400 4800
Wire Wire Line
	2300 4250 2300 4350
$Comp
L power:GND #PWR0110
U 1 1 5D474D63
P 1450 4900
F 0 "#PWR0110" H 1450 4650 50  0001 C CNN
F 1 "GND" H 1455 4727 50  0000 C CNN
F 2 "" H 1450 4900 50  0001 C CNN
F 3 "" H 1450 4900 50  0001 C CNN
	1    1450 4900
	1    0    0    -1  
$EndComp
$Comp
L Switch:SW_Push_SPDT SW1
U 1 1 5D47AFC5
P 1750 4550
F 0 "SW1" H 1750 4835 50  0000 C CNN
F 1 "SW_Push_SPDT" H 1750 4744 50  0000 C CNN
F 2 "USR-Footprints:XKB7070-Z" H 1750 4550 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1811191808_XKB-XKB7070-Z_C318863.pdf" H 1750 4550 50  0001 C CNN
	1    1750 4550
	-1   0    0    -1  
$EndComp
Wire Wire Line
	1950 4550 2000 4550
Wire Wire Line
	1200 4250 1450 4250
Wire Wire Line
	1550 4650 1450 4650
Wire Wire Line
	1450 4650 1450 4900
Wire Wire Line
	1550 4450 1450 4450
Wire Wire Line
	1450 4450 1450 4250
Connection ~ 1450 4250
Wire Wire Line
	1450 4250 2300 4250
Text GLabel 6700 3750 3    50   Input ~ 0
RESET
Wire Wire Line
	3550 3450 3700 3450
Connection ~ 3700 3450
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5D4A1496
P 1450 3450
F 0 "#FLG0101" H 1450 3525 50  0001 C CNN
F 1 "PWR_FLAG" H 1450 3623 50  0000 C CNN
F 2 "" H 1450 3450 50  0001 C CNN
F 3 "~" H 1450 3450 50  0001 C CNN
	1    1450 3450
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5D4A3D51
P 2000 3450
F 0 "#FLG0103" H 2000 3525 50  0001 C CNN
F 1 "PWR_FLAG" H 2000 3623 50  0000 C CNN
F 2 "" H 2000 3450 50  0001 C CNN
F 3 "~" H 2000 3450 50  0001 C CNN
	1    2000 3450
	-1   0    0    1   
$EndComp
Text GLabel 2000 3250 1    50   Input ~ 0
+3V3
Text GLabel 1450 3250 1    50   Input ~ 0
VIN
Wire Wire Line
	2000 3450 2000 3250
Wire Wire Line
	1450 3450 1450 3250
Wire Wire Line
	1700 3550 1700 3700
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5D4A1B11
P 1700 3550
F 0 "#FLG0102" H 1700 3625 50  0001 C CNN
F 1 "PWR_FLAG" H 1700 3723 50  0000 C CNN
F 2 "" H 1700 3550 50  0001 C CNN
F 3 "~" H 1700 3550 50  0001 C CNN
	1    1700 3550
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5D4ADA6B
P 1700 3700
F 0 "#PWR0111" H 1700 3450 50  0001 C CNN
F 1 "GND" H 1705 3527 50  0000 C CNN
F 2 "" H 1700 3700 50  0001 C CNN
F 3 "" H 1700 3700 50  0001 C CNN
	1    1700 3700
	1    0    0    -1  
$EndComp
Text GLabel 2450 3450 0    50   Input ~ 0
VIN
Text GLabel 2400 4800 2    50   Input ~ 0
VIN
Wire Wire Line
	4200 4900 4400 4900
$Comp
L power:GND #PWR0108
U 1 1 5CDC439C
P 4400 4900
F 0 "#PWR0108" H 4400 4650 50  0001 C CNN
F 1 "GND" H 4405 4727 50  0000 C CNN
F 2 "" H 4400 4900 50  0001 C CNN
F 3 "" H 4400 4900 50  0001 C CNN
	1    4400 4900
	1    0    0    -1  
$EndComp
Text Label 4200 4900 0    50   ~ 0
GND
Text Label 1200 4250 0    50   ~ 0
VINJACK
Wire Wire Line
	4400 4700 4200 4700
Text GLabel 4400 4700 2    50   Input ~ 0
VIN
Text Label 4200 4700 0    50   ~ 0
VIN
$Comp
L Connector:TestPoint TP1
U 1 1 5D573650
P 6200 2250
F 0 "TP1" V 6154 2438 50  0000 L CNN
F 1 "Debug" V 6245 2438 50  0000 L CNN
F 2 "TestPoint:TestPoint_THTPad_D1.0mm_Drill0.5mm" H 6400 2250 50  0001 C CNN
F 3 "~" H 6400 2250 50  0001 C CNN
	1    6200 2250
	0    1    1    0   
$EndComp
Wire Wire Line
	5900 2250 6200 2250
$Comp
L _electromech:PUSH SW2
U 1 1 5D576BAE
P 6950 3750
F 0 "SW2" H 6950 3970 50  0000 C CNN
F 1 "PUSH" H 6950 3879 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_FSMSM" H 6950 3750 60  0001 C CNN
F 3 "" H 6950 3750 60  0000 C CNN
	1    6950 3750
	1    0    0    -1  
$EndComp
Wire Wire Line
	7100 3750 7450 3750
$Comp
L Memory_Flash:AT25DF041x-UxN-x U4
U 1 1 5D593F0F
P 3150 1700
F 0 "U4" H 3794 1746 50  0000 L CNN
F 1 "AT25DF512x-UxN-x" H 3794 1655 50  0000 L CNN
F 2 "Package_SO:SOIC-8-1EP_3.9x4.9mm_P1.27mm_EP2.29x3mm" H 2950 1100 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Adesto-Technologies-AT25DF512C-MAHN-T_C226099.pdf" H 3150 2400 50  0001 C CNN
	1    3150 1700
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR02
U 1 1 5D59ADFA
P 3150 2300
F 0 "#PWR02" H 3150 2050 50  0001 C CNN
F 1 "GND" H 3155 2127 50  0000 C CNN
F 2 "" H 3150 2300 50  0001 C CNN
F 3 "" H 3150 2300 50  0001 C CNN
	1    3150 2300
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 2300 3150 2200
Text GLabel 3150 1100 1    50   Input ~ 0
+3V3
Wire Wire Line
	3150 1100 3150 1150
Text GLabel 3900 1500 2    50   Input ~ 0
MISO
Wire Wire Line
	3900 1500 3750 1500
Text GLabel 2400 1500 0    50   Input ~ 0
MOSI
Wire Wire Line
	2400 1500 2550 1500
Text GLabel 2400 1600 0    50   Input ~ 0
SCK
Wire Wire Line
	2400 1600 2550 1600
Wire Wire Line
	2550 1900 2400 1900
Wire Wire Line
	1900 1150 1900 1900
Connection ~ 3150 1150
Wire Wire Line
	3150 1150 3150 1200
Wire Wire Line
	2550 1800 2400 1800
Wire Wire Line
	2400 1800 2400 1900
Connection ~ 2400 1900
Text GLabel 2400 1700 0    50   Input ~ 0
FLASH_CSN
Wire Wire Line
	2400 1700 2500 1700
Wire Wire Line
	1900 1900 2400 1900
Wire Wire Line
	1900 1150 2500 1150
$Comp
L Device:R_Small R4
U 1 1 5D5C158E
P 2500 1300
F 0 "R4" H 2559 1346 50  0000 L CNN
F 1 "1k" H 2559 1255 50  0000 L CNN
F 2 "Resistor_SMD:R_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 2500 1300 50  0001 C CNN
F 3 "~" H 2500 1300 50  0001 C CNN
	1    2500 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	2500 1200 2500 1150
Connection ~ 2500 1150
Wire Wire Line
	2500 1150 3150 1150
Wire Wire Line
	2500 1400 2500 1700
Connection ~ 2500 1700
Wire Wire Line
	2500 1700 2550 1700
Text GLabel 6050 2450 2    50   Input ~ 0
FLASH_CSN
NoConn ~ 5900 2350
Wire Wire Line
	5900 2450 6050 2450
Connection ~ 6350 3750
Wire Wire Line
	5900 3750 6350 3750
$Comp
L Device:C C4
U 1 1 5D615393
P 4800 1500
F 0 "C4" H 4915 1546 50  0000 L CNN
F 1 "100n" H 4915 1455 50  0000 L CNN
F 2 "Capacitor_SMD:C_0603_1608Metric_Pad1.05x0.95mm_HandSolder" H 4838 1350 50  0001 C CNN
F 3 "~" H 4800 1500 50  0001 C CNN
	1    4800 1500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR03
U 1 1 5D619490
P 4800 1750
F 0 "#PWR03" H 4800 1500 50  0001 C CNN
F 1 "GND" H 4805 1577 50  0000 C CNN
F 2 "" H 4800 1750 50  0001 C CNN
F 3 "" H 4800 1750 50  0001 C CNN
	1    4800 1750
	1    0    0    -1  
$EndComp
Text GLabel 4800 1200 1    50   Input ~ 0
+3V3
Wire Wire Line
	4800 1200 4800 1350
Wire Wire Line
	4800 1650 4800 1750
Wire Wire Line
	10500 2650 10650 2650
Wire Wire Line
	10500 3650 10500 4300
Wire Wire Line
	8300 3650 8300 4300
$Comp
L MOUDLE-BLUETOOTH-HC-05_34P-27X13MM_:MOUDLE-BLUETOOTH-HC-05(34P-27X13MM) U2
U 1 1 5CB7CCE4
P 9400 3100
F 0 "U2" H 9400 4017 50  0000 C CNN
F 1 "HC-05" H 9400 3926 50  0000 C CNN
F 2 "USR-Footprints:HC-05" H 9400 3100 50  0001 L BNN
F 3 "https://components101.com/sites/default/files/component_datasheet/HC-05%20Datasheet.pdf" H 9400 3100 50  0001 L BNN
F 4 "Unavailable" H 9400 3100 50  0001 L BNN "Field4"
F 5 "SOIC-14" H 9400 3100 50  0001 L BNN "Field6"
F 6 "HuiCheng" H 9400 3100 50  0001 L BNN "Field7"
F 7 "None" H 9400 3100 50  0001 L BNN "Field8"
	1    9400 3100
	1    0    0    -1  
$EndComp
NoConn ~ 10500 3450
$EndSCHEMATC
