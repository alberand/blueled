EESchema Schematic File Version 4
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
P 6000 2750
F 0 "U1" H 6000 1800 50  0000 C CNN
F 1 "ATmega328P-AU" H 6000 1700 50  0000 C CNN
F 2 "Package_QFP:TQFP-32_7x7mm_P0.8mm" H 6000 2750 50  0001 C CIN
F 3 "http://ww1.microchip.com/downloads/en/DeviceDoc/ATmega328_P%20AVR%20MCU%20with%20picoPower%20Technology%20Data%20Sheet%2040001984A.pdf" H 6000 2750 50  0001 C CNN
F 4 "lcsc.com" H 6000 2750 50  0001 C CNN "Distributor"
F 5 "ATmega328P-AU" H 6000 2750 50  0001 C CNN "Manuf. Part"
	1    6000 2750
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0101
U 1 1 5CAFFAEC
P 3150 1850
F 0 "#PWR0101" H 3150 1600 50  0001 C CNN
F 1 "GND" H 3155 1677 50  0000 C CNN
F 2 "" H 3150 1850 50  0001 C CNN
F 3 "" H 3150 1850 50  0001 C CNN
	1    3150 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	3150 1500 3150 1600
Wire Wire Line
	2600 1500 2600 1600
Wire Wire Line
	2600 1600 3150 1600
Connection ~ 3150 1600
Wire Wire Line
	3600 1500 3600 1600
Wire Wire Line
	3150 1600 3600 1600
$Comp
L power:GND #PWR0103
U 1 1 5CB803CB
P 6000 4350
F 0 "#PWR0103" H 6000 4100 50  0001 C CNN
F 1 "GND" H 6005 4177 50  0000 C CNN
F 2 "" H 6000 4350 50  0001 C CNN
F 3 "" H 6000 4350 50  0001 C CNN
	1    6000 4350
	1    0    0    -1  
$EndComp
$Comp
L Regulator_Linear:LM1117-3.3 U3
U 1 1 5CB83042
P 3150 1200
F 0 "U3" H 3150 1442 50  0000 C CNN
F 1 "AMS1117-3.3" H 3150 1351 50  0000 C CNN
F 2 "Package_TO_SOT_SMD:SOT-223" H 3150 1200 50  0001 C CNN
F 3 "http://www.ti.com/lit/ds/symlink/lm1117.pdf" H 3150 1200 50  0001 C CNN
F 4 "lcsc.com" H 3150 1200 50  0001 C CNN "Distributor"
F 5 "AMS1117-3.3" H 3150 1200 50  0001 C CNN "Manuf. Part"
	1    3150 1200
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 1150 6100 1150
Wire Wire Line
	6100 1150 6100 1250
Wire Wire Line
	6000 1150 6000 1250
$Comp
L Device:C C3
U 1 1 5CBEE490
P 5250 1700
F 0 "C3" H 5365 1746 50  0000 L CNN
F 1 "100n" H 5365 1655 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 5288 1550 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1810191215_Samsung-Electro-Mechanics-CL21B104KBCNNNC_C1711.pdf" H 5250 1700 50  0001 C CNN
F 4 "lcsc.com" H 5250 1700 50  0001 C CNN "Distributor"
F 5 "CL21B104KBCNNNC" H 5250 1700 50  0001 C CNN "Manuf. Part"
	1    5250 1700
	-1   0    0    1   
$EndComp
$Comp
L power:GND #PWR0106
U 1 1 5CBEF7A5
P 5250 2050
F 0 "#PWR0106" H 5250 1800 50  0001 C CNN
F 1 "GND" H 5255 1877 50  0000 C CNN
F 2 "" H 5250 2050 50  0001 C CNN
F 3 "" H 5250 2050 50  0001 C CNN
	1    5250 2050
	1    0    0    -1  
$EndComp
$Comp
L Device:R_Small R2
U 1 1 5CBF3B20
P 4050 1350
F 0 "R2" H 4109 1396 50  0000 L CNN
F 1 "1k" H 4109 1305 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4050 1350 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1810301711_KOA-Speer-Elec-RK73B2ATTD102J_C159911.pdf" H 4050 1350 50  0001 C CNN
F 4 "lcsc.com" H 4050 1350 50  0001 C CNN "Distributor"
F 5 "RK73B2ATTD102J" H 4050 1350 50  0001 C CNN "Manuf. Part"
	1    4050 1350
	1    0    0    -1  
$EndComp
$Comp
L Device:LED D1
U 1 1 5CBF4695
P 4050 1650
F 0 "D1" V 4089 1533 50  0000 R CNN
F 1 "LED" V 3998 1533 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 4050 1650 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1811141223_TOGIALED-TJ-S1608SW6TGLC2G-A5_C192316.pdf" H 4050 1650 50  0001 C CNN
F 4 "lcsc.com" H 4050 1650 50  0001 C CNN "Distributor"
F 5 "TJ-S1608SW6TGLC2G-A5 " H 4050 1650 50  0001 C CNN "Manuf. Part"
	1    4050 1650
	0    -1   -1   0   
$EndComp
Wire Wire Line
	4050 1450 4050 1500
Wire Wire Line
	4050 1250 4050 1200
Connection ~ 4050 1200
Wire Wire Line
	4050 1200 4150 1200
Text Label 1350 1400 0    50   ~ 0
GND
$Comp
L power:GND #PWR0109
U 1 1 5CC59A0A
P 1350 1400
F 0 "#PWR0109" H 1350 1150 50  0001 C CNN
F 1 "GND" H 1355 1227 50  0000 C CNN
F 2 "" H 1350 1400 50  0001 C CNN
F 3 "" H 1350 1400 50  0001 C CNN
	1    1350 1400
	1    0    0    -1  
$EndComp
Text Label 6000 1050 0    50   ~ 0
+3V3
Text Label 10550 1500 0    50   ~ 0
DATA
$Comp
L Connector:Screw_Terminal_01x03 J2
U 1 1 5CC5BA14
P 10150 1500
F 0 "J2" H 10230 1542 50  0000 L CNN
F 1 "LED Strip" H 10230 1451 50  0000 L CNN
F 2 "TerminalBlock:TerminalBlock_bornier-3_P5.08mm" H 10150 1500 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1811151432_Phoenix-Contact-1729131_C91154.pdf" H 10150 1500 50  0001 C CNN
F 4 "lcsc.com" H 10150 1500 50  0001 C CNN "Distributor"
F 5 "1729131" H 10150 1500 50  0001 C CNN "Manuf. Part"
	1    10150 1500
	-1   0    0    -1  
$EndComp
NoConn ~ 6600 2950
NoConn ~ 6600 2850
NoConn ~ 6600 2750
NoConn ~ 6600 2650
NoConn ~ 6600 2550
NoConn ~ 6600 2450
NoConn ~ 5400 1750
NoConn ~ 5400 1850
$Comp
L Connector:Barrel_Jack J1
U 1 1 5CDBC439
P 1050 1300
F 0 "J1" H 1107 1625 50  0000 C CNN
F 1 "Barrel_Jack" H 1107 1534 50  0000 C CNN
F 2 "Connector_BarrelJack:BarrelJack_Horizontal" H 1100 1260 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1912111437_XKB-Enterprise-DC-005-5A-2-0_C381116.pdf" H 1100 1260 50  0001 C CNN
F 4 "lcsc.com" H 1050 1300 50  0001 C CNN "Distributor"
F 5 "DC-005-5A-2.0" H 1050 1300 50  0001 C CNN "Manuf. Part"
	1    1050 1300
	1    0    0    -1  
$EndComp
Wire Wire Line
	10350 1500 10550 1500
$Comp
L power:GND #PWR0107
U 1 1 5CBF586D
P 4050 1850
F 0 "#PWR0107" H 4050 1600 50  0001 C CNN
F 1 "GND" H 4055 1677 50  0000 C CNN
F 2 "" H 4050 1850 50  0001 C CNN
F 3 "" H 4050 1850 50  0001 C CNN
	1    4050 1850
	1    0    0    -1  
$EndComp
Wire Wire Line
	4050 1800 4050 1850
Wire Wire Line
	3150 1600 3150 1850
Text Notes 7350 7500 0    50   ~ 0
Bluetooth Ledstrip controller
Text Notes 8150 7650 0    50   ~ 0
14/05/2019
Text Notes 8200 7750 0    50   ~ 0
alberand
$Comp
L Connector_Generic:Conn_02x03_Top_Bottom J3
U 1 1 5D06C568
P 9100 1550
F 0 "J3" H 9150 1867 50  0000 C CNN
F 1 "ICSP" H 9150 1776 50  0000 C CNN
F 2 "Connector_PinHeader_2.54mm:PinHeader_2x03_P2.54mm_Vertical" H 9100 1550 50  0001 C CNN
F 3 "~" H 9100 1550 50  0001 C CNN
	1    9100 1550
	1    0    0    -1  
$EndComp
Wire Wire Line
	9600 1450 9400 1450
Wire Wire Line
	8650 1550 8900 1550
Wire Wire Line
	8650 1450 8900 1450
Wire Wire Line
	9400 1550 9600 1550
$Comp
L power:GND #PWR01
U 1 1 5D07BC0F
P 9450 1750
F 0 "#PWR01" H 9450 1500 50  0001 C CNN
F 1 "GND" H 9455 1577 50  0000 C CNN
F 2 "" H 9450 1750 50  0001 C CNN
F 3 "" H 9450 1750 50  0001 C CNN
	1    9450 1750
	1    0    0    -1  
$EndComp
Wire Wire Line
	9400 1650 9450 1650
Wire Wire Line
	9450 1650 9450 1750
Text Label 8650 1650 0    50   ~ 0
RESET
Wire Wire Line
	8650 1650 8900 1650
$Comp
L Device:Q_PMOS_SDG Q1
U 1 1 5D461D8C
P 2300 1300
F 0 "Q1" V 2650 1250 50  0000 L CNN
F 1 "Q_PMOS_SDG" V 2550 1050 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:TO-252-3_TabPin4" H 2500 1400 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/Alpha-Omega-Semicon-AOS-AOD4185_C77993.pdf" H 2300 1300 50  0001 C CNN
F 4 "lcsc.com" H 2300 1300 50  0001 C CNN "Distributor"
F 5 "AOD4185L" H 2300 1300 50  0001 C CNN "Manuf. Part"
	1    2300 1300
	0    -1   -1   0   
$EndComp
Wire Wire Line
	10350 1600 10550 1600
$Comp
L power:GND #PWR0108
U 1 1 5CDC439C
P 10550 1600
F 0 "#PWR0108" H 10550 1350 50  0001 C CNN
F 1 "GND" H 10555 1427 50  0000 C CNN
F 2 "" H 10550 1600 50  0001 C CNN
F 3 "" H 10550 1600 50  0001 C CNN
	1    10550 1600
	1    0    0    -1  
$EndComp
Wire Wire Line
	10550 1400 10350 1400
Text Label 10550 1400 0    50   ~ 0
VIN
$Comp
L Connector:TestPoint TP1
U 1 1 5D573650
P 6900 1550
F 0 "TP1" V 6854 1738 50  0000 L CNN
F 1 "Debug" V 6945 1738 50  0000 L CNN
F 2 "TestPoint:TestPoint_Pad_D1.5mm" H 7100 1550 50  0001 C CNN
F 3 "~" H 7100 1550 50  0001 C CNN
	1    6900 1550
	0    1    1    0   
$EndComp
Wire Wire Line
	6600 1550 6900 1550
$Comp
L Memory_Flash:AT25SF081-SSHF-X U4
U 1 1 5D593F0F
P 2050 3450
F 0 "U4" H 2000 3450 50  0000 L CNN
F 1 "AT25SF081" H 2000 3350 50  0000 L CNN
F 2 "Package_SO:SOIC-8_3.9x4.9mm_P1.27mm" H 1850 2850 50  0001 C CNN
F 3 "https://www.adestotech.com/wp-content/uploads/DS-AT25SF081_045.pdf" H 2050 4150 50  0001 C CNN
F 4 "lcsc.com" H 2050 3450 50  0001 C CNN "Distributor"
F 5 "AT25SF081-SHD-T" H 2050 3450 50  0001 C CNN "Manuf. Part"
	1    2050 3450
	1    0    0    -1  
$EndComp
Connection ~ 2050 2900
Wire Wire Line
	2050 2900 2050 2950
$Comp
L Device:R_Small R4
U 1 1 5D5C158E
P 1400 3050
F 0 "R4" H 1459 3096 50  0000 L CNN
F 1 "1k" H 1459 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1400 3050 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1810301711_KOA-Speer-Elec-RK73B2ATTD102J_C159911.pdf" H 1400 3050 50  0001 C CNN
F 4 "lcsc.com" H 1400 3050 50  0001 C CNN "Distributor"
F 5 "RK73B2ATTD102J" H 1400 3050 50  0001 C CNN "Manuf. Part"
	1    1400 3050
	1    0    0    -1  
$EndComp
Wire Wire Line
	1400 2950 1400 2900
Connection ~ 1400 2900
Wire Wire Line
	1400 2900 2050 2900
Wire Wire Line
	1400 3150 1400 3450
Wire Wire Line
	1400 3450 1450 3450
NoConn ~ 6600 1650
Text Label 1350 1200 0    50   ~ 0
VINJACK
Wire Wire Line
	1350 1200 1600 1200
Connection ~ 1600 1200
Wire Wire Line
	1600 1200 2100 1200
Wire Wire Line
	1300 3650 1450 3650
Wire Wire Line
	1300 2900 1400 2900
Wire Wire Line
	1200 3350 1450 3350
Wire Wire Line
	1200 3250 1450 3250
Text Label 6700 3250 0    50   ~ 0
RX
Text Label 6700 3350 0    50   ~ 0
TX
Text Label 6700 3450 0    50   ~ 0
HC-STATE
Text Label 6700 3550 0    50   ~ 0
HC-ATMODE
Text Label 6700 3650 0    50   ~ 0
~HC-POWER-EN
Text Label 6700 3750 0    50   ~ 0
HC-DISCNCT
Text Label 6700 3950 0    50   ~ 0
DATA
Wire Wire Line
	6600 3450 6700 3450
Wire Wire Line
	6600 3550 6700 3550
Wire Wire Line
	6600 3650 6700 3650
Wire Wire Line
	6600 3750 6700 3750
Wire Wire Line
	6600 3950 6700 3950
Wire Wire Line
	6600 3250 6700 3250
Wire Wire Line
	6600 3350 6700 3350
Text Label 6700 1850 0    50   ~ 0
MOSI
Text Label 6700 1950 0    50   ~ 0
MISO
Text Label 6700 2050 0    50   ~ 0
SCK
Wire Wire Line
	6600 1850 6700 1850
Wire Wire Line
	6600 1950 6700 1950
Wire Wire Line
	6600 2050 6700 2050
Text Label 4150 1200 0    50   ~ 0
+3V3
Text Label 2600 1200 2    50   ~ 0
VIN
Text Label 8650 1450 0    50   ~ 0
MISO
Text Label 8650 1550 0    50   ~ 0
SCK
Text Label 9600 1450 2    50   ~ 0
+3V3
Text Label 9600 1550 2    50   ~ 0
MOSI
Text Label 2750 3250 0    50   ~ 0
MISO
Wire Wire Line
	2650 3250 2750 3250
Text Label 3100 2800 0    50   ~ 0
+3V3
Text Label 1200 3250 2    50   ~ 0
MOSI
Text Label 1200 3350 2    50   ~ 0
SCK
Wire Wire Line
	6000 1150 6000 1050
Connection ~ 6000 1150
Text Label 6850 2650 2    50   ~ 0
+3V3
Wire Wire Line
	3100 2900 3100 3050
$Comp
L power:GND #PWR03
U 1 1 5D619490
P 3100 4050
F 0 "#PWR03" H 3100 3800 50  0001 C CNN
F 1 "GND" H 3105 3877 50  0000 C CNN
F 2 "" H 3100 4050 50  0001 C CNN
F 3 "" H 3100 4050 50  0001 C CNN
	1    3100 4050
	1    0    0    -1  
$EndComp
$Comp
L Device:C C4
U 1 1 5D615393
P 3100 3200
F 0 "C4" H 3215 3246 50  0000 L CNN
F 1 "100n" H 3215 3155 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3138 3050 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1810191215_Samsung-Electro-Mechanics-CL21B104KBCNNNC_C1711.pdf" H 3100 3200 50  0001 C CNN
F 4 "lcsc.com" H 3100 3200 50  0001 C CNN "Distributor"
F 5 "CL21B104KBCNNNC" H 3100 3200 50  0001 C CNN "Manuf. Part"
	1    3100 3200
	1    0    0    -1  
$EndComp
Wire Wire Line
	2050 2900 3100 2900
Wire Wire Line
	3100 2800 3100 2900
Connection ~ 3100 2900
Wire Wire Line
	3100 3350 3100 3950
Wire Wire Line
	3100 3950 2050 3950
Wire Wire Line
	3100 4050 3100 3950
Connection ~ 3100 3950
Text Notes 850  800  0    89   ~ 0
LED strip & MCU POWER
Text Notes 900  2700 0    89   ~ 0
FLASH Memory
Text Notes 8600 1100 0    89   ~ 0
Ports
Wire Wire Line
	2800 7150 2800 7050
Wire Wire Line
	1800 5300 2100 5300
Connection ~ 1800 5300
Wire Wire Line
	1800 5100 1800 5300
Wire Wire Line
	1700 5300 1800 5300
Wire Wire Line
	1700 5200 2000 5200
Wire Wire Line
	1800 4450 1800 4550
Text Label 1800 4450 0    50   ~ 0
+3V3
Wire Wire Line
	1800 4850 1800 4900
$Comp
L Device:LED D3
U 1 1 5ED22AF5
P 1800 4700
F 0 "D3" V 1850 4900 50  0000 R CNN
F 1 "LED" V 1750 4900 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1800 4700 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1811141223_TOGIALED-TJ-S1608SW6TGLC2R-A5_C192315.pdf" H 1800 4700 50  0001 C CNN
F 4 "lcsc.com" H 1800 4700 50  0001 C CNN "Distributor"
F 5 "TJ-S1608SW6TGLC2R-A5 " H 1800 4700 50  0001 C CNN "Manuf. Part"
	1    1800 4700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R6
U 1 1 5ED22AEB
P 1800 5000
F 0 "R6" H 1859 5046 50  0000 L CNN
F 1 "1k" H 1859 4955 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1800 5000 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1810301711_KOA-Speer-Elec-RK73B2ATTD102J_C159911.pdf" H 1800 5000 50  0001 C CNN
F 4 "lcsc.com" H 1800 5000 50  0001 C CNN "Distributor"
F 5 "RK73B2ATTD102J" H 1800 5000 50  0001 C CNN "Manuf. Part"
	1    1800 5000
	1    0    0    -1  
$EndComp
Connection ~ 2000 5200
Wire Wire Line
	2000 5200 2100 5200
Text Label 1700 5300 2    50   ~ 0
TX
Wire Wire Line
	2000 4450 2000 4550
Wire Wire Line
	4300 6200 4400 6200
Text Label 4400 6200 0    50   ~ 0
HC-STATE
Text Label 4400 6300 0    50   ~ 0
HC-DISCNCT
Text Label 4450 5200 0    50   ~ 0
HC-ATMODE
Text Label 2000 4450 0    50   ~ 0
+3V3
Text Label 1700 5200 2    50   ~ 0
RX
NoConn ~ 4300 5400
Wire Wire Line
	2100 6400 2100 7050
Wire Wire Line
	4300 6400 4300 7050
Wire Wire Line
	4300 5200 4450 5200
Wire Wire Line
	4300 6300 4400 6300
Wire Wire Line
	2000 5100 2000 5200
Wire Wire Line
	2000 4850 2000 4900
$Comp
L Device:LED D2
U 1 1 5D08942B
P 2000 4700
F 0 "D2" V 2039 4583 50  0000 R CNN
F 1 "LED" V 1948 4583 50  0000 R CNN
F 2 "LED_SMD:LED_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2000 4700 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1811141223_TOGIALED-TJ-S1608SW6TGLC2R-A5_C192315.pdf" H 2000 4700 50  0001 C CNN
F 4 "lcsc.com" H 2000 4700 50  0001 C CNN "Distributor"
F 5 "TJ-S1608SW6TGLC2R-A5 " H 2000 4700 50  0001 C CNN "Manuf. Part"
	1    2000 4700
	0    -1   -1   0   
$EndComp
$Comp
L Device:R_Small R3
U 1 1 5D089425
P 2000 5000
F 0 "R3" H 2059 5046 50  0000 L CNN
F 1 "1k" H 2059 4955 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2000 5000 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1810301711_KOA-Speer-Elec-RK73B2ATTD102J_C159911.pdf" H 2000 5000 50  0001 C CNN
F 4 "lcsc.com" H 2000 5000 50  0001 C CNN "Distributor"
F 5 "RK73B2ATTD102J" H 2000 5000 50  0001 C CNN "Manuf. Part"
	1    2000 5000
	1    0    0    -1  
$EndComp
NoConn ~ 3500 6800
NoConn ~ 3400 6800
NoConn ~ 3300 6800
NoConn ~ 3100 6800
NoConn ~ 3000 6800
NoConn ~ 2900 6800
NoConn ~ 4300 6100
NoConn ~ 4300 6000
NoConn ~ 4300 5900
NoConn ~ 4300 5800
NoConn ~ 4300 5700
NoConn ~ 4300 5600
NoConn ~ 4300 5500
NoConn ~ 4300 5300
NoConn ~ 2100 6100
NoConn ~ 2100 6000
NoConn ~ 2100 5900
NoConn ~ 2100 5800
NoConn ~ 2100 5700
NoConn ~ 2100 5600
NoConn ~ 2100 5500
NoConn ~ 2100 5400
Text Label 2850 7050 0    50   ~ 0
GND
Wire Wire Line
	2100 7050 2800 7050
Wire Wire Line
	2800 6800 2800 7050
Wire Wire Line
	3600 7050 2800 7050
Wire Wire Line
	3600 6800 3600 7050
Connection ~ 2800 7050
Connection ~ 3600 7050
Wire Wire Line
	4300 7050 3600 7050
$Comp
L power:GND #PWR0102
U 1 1 5CB7FE99
P 2800 7150
F 0 "#PWR0102" H 2800 6900 50  0001 C CNN
F 1 "GND" H 2805 6977 50  0000 C CNN
F 2 "" H 2800 7150 50  0001 C CNN
F 3 "" H 2800 7150 50  0001 C CNN
	1    2800 7150
	1    0    0    -1  
$EndComp
Text Label 1900 7000 2    50   ~ 0
+3V3
Text Label 1200 6600 2    50   ~ 0
~HC-POWER-EN
$Comp
L Device:R_Small R5
U 1 1 5E8E07EF
P 1400 6600
F 0 "R5" H 1459 6646 50  0000 L CNN
F 1 "1k" H 1459 6555 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1400 6600 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1810301711_KOA-Speer-Elec-RK73B2ATTD102J_C159911.pdf" H 1400 6600 50  0001 C CNN
F 4 "lcsc.com" H 1400 6600 50  0001 C CNN "Distributor"
F 5 "RK73B2ATTD102J" H 1400 6600 50  0001 C CNN "Manuf. Part"
	1    1400 6600
	0    1    1    0   
$EndComp
Wire Wire Line
	1500 6600 1600 6600
Wire Wire Line
	1900 6800 1900 7000
$Comp
L Device:Q_PNP_EBC Q2
U 1 1 5E8AAEF6
P 1800 6600
F 0 "Q2" H 1450 6900 50  0000 L CNN
F 1 "Q_PNP_EBC" H 1450 6800 50  0000 L CNN
F 2 "Package_TO_SOT_SMD:SOT-323_SC-70_Handsoldering" H 2000 6700 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1808280000_ROHM-Semicon-UMT2907A_C122972.pdf" H 1800 6600 50  0001 C CNN
F 4 "lcsc.com" H 1800 6600 50  0001 C CNN "Distributor"
F 5 "UMT2907A" H 1800 6600 50  0001 C CNN "Manuf. Part"
	1    1800 6600
	1    0    0    -1  
$EndComp
Wire Wire Line
	5250 1550 5400 1550
Text Notes 900  4300 0    89   ~ 0
HC-05 Bluetooth
Text Notes 4700 750  0    89   ~ 0
ATmega328P
Wire Wire Line
	1450 3550 1300 3550
Wire Wire Line
	1300 3550 1300 3650
Wire Wire Line
	1900 6400 1900 6300
Wire Wire Line
	1900 6300 2100 6300
Wire Wire Line
	1300 6600 1200 6600
Text Notes 8650 2250 0    89   ~ 0
KiCAD ad-hoc
Text Label 8850 2450 2    50   ~ 0
VIN
Text Label 9500 2450 2    50   ~ 0
+3V3
Wire Wire Line
	8850 2650 8850 2450
Wire Wire Line
	9500 2650 9500 2450
$Comp
L power:PWR_FLAG #FLG0103
U 1 1 5D4A3D51
P 9500 2650
F 0 "#FLG0103" H 9500 2900 50  0000 C CNN
F 1 "PWR_FLAG" H 9500 2823 50  0000 C CNN
F 2 "" H 9500 2650 50  0001 C CNN
F 3 "~" H 9500 2650 50  0001 C CNN
	1    9500 2650
	-1   0    0    1   
$EndComp
$Comp
L power:PWR_FLAG #FLG0101
U 1 1 5D4A1496
P 8850 2650
F 0 "#FLG0101" H 8850 2900 50  0000 C CNN
F 1 "PWR_FLAG" H 8850 2823 50  0000 C CNN
F 2 "" H 8850 2650 50  0001 C CNN
F 3 "~" H 8850 2650 50  0001 C CNN
	1    8850 2650
	-1   0    0    1   
$EndComp
$Comp
L Device:R_Small R7
U 1 1 5EFA213D
P 1300 3050
F 0 "R7" H 1359 3096 50  0000 L CNN
F 1 "1k" H 1359 3005 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 1300 3050 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1810301711_KOA-Speer-Elec-RK73B2ATTD102J_C159911.pdf" H 1300 3050 50  0001 C CNN
F 4 "lcsc.com" H 1300 3050 50  0001 C CNN "Distributor"
F 5 "RK73B2ATTD102J" H 1300 3050 50  0001 C CNN "Manuf. Part"
	1    1300 3050
	-1   0    0    1   
$EndComp
Wire Wire Line
	1300 2900 1300 2950
Wire Wire Line
	1300 3150 1300 3550
Connection ~ 1300 3550
Wire Wire Line
	9150 2500 9150 2650
$Comp
L power:PWR_FLAG #FLG0102
U 1 1 5D4A1B11
P 9150 2500
F 0 "#FLG0102" H 9150 2575 50  0001 C CNN
F 1 "PWR_FLAG" H 9150 2673 50  0000 C CNN
F 2 "" H 9150 2500 50  0001 C CNN
F 3 "~" H 9150 2500 50  0001 C CNN
	1    9150 2500
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0111
U 1 1 5D4ADA6B
P 9150 2650
F 0 "#PWR0111" H 9150 2400 50  0001 C CNN
F 1 "GND" H 9155 2477 50  0000 C CNN
F 2 "" H 9150 2650 50  0001 C CNN
F 3 "" H 9150 2650 50  0001 C CNN
	1    9150 2650
	1    0    0    -1  
$EndComp
Wire Wire Line
	6000 4250 6000 4350
$Comp
L Device:C C2
U 1 1 5E94312D
P 3600 1350
F 0 "C2" H 3400 1400 50  0000 L CNN
F 1 "10uF" H 3300 1300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 3638 1200 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1810191226_Samsung-Electro-Mechanics-CL21A106MQFNNNE_C41893.pdf" H 3600 1350 50  0001 C CNN
F 4 "lcsc.com" H 3600 1350 50  0001 C CNN "Distributor"
F 5 "CL21A106MQFNNNE" H 3600 1350 50  0001 C CNN "Manuf. Part"
	1    3600 1350
	-1   0    0    1   
$EndComp
Wire Wire Line
	3450 1200 3600 1200
Connection ~ 3600 1200
Wire Wire Line
	3600 1200 4050 1200
Wire Wire Line
	7500 3150 7500 3050
$Comp
L blueled-rescue:PUSH-_electromech SW2
U 1 1 5D576BAE
P 7350 3050
F 0 "SW2" H 7350 3270 50  0000 C CNN
F 1 "PUSH" H 7350 3179 50  0000 C CNN
F 2 "Button_Switch_SMD:SW_SPST_FSMSM" H 7350 3050 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1811082126_Korean-Hroparts-Elec-K2-1107ST-A4SW-06_C118141.pdf" H 7350 3050 60  0001 C CNN
F 4 "lcsc.com" H 7350 3050 50  0001 C CNN "Distributor"
F 5 "K2-1107ST-A4SW-06" H 7350 3050 50  0001 C CNN "Manuf. Part"
	1    7350 3050
	1    0    0    -1  
$EndComp
$Comp
L power:GND #PWR0105
U 1 1 5CBEBE63
P 7500 3150
F 0 "#PWR0105" H 7500 2900 50  0001 C CNN
F 1 "GND" H 7505 2977 50  0000 C CNN
F 2 "" H 7500 3150 50  0001 C CNN
F 3 "" H 7500 3150 50  0001 C CNN
	1    7500 3150
	1    0    0    -1  
$EndComp
Text Label 6950 3050 0    50   ~ 0
RESET
Wire Wire Line
	6600 3050 6850 3050
Wire Wire Line
	6850 3050 6850 2950
Wire Wire Line
	6850 2750 6850 2650
$Comp
L Device:R_Small R1
U 1 1 5CBE0D3A
P 6850 2850
F 0 "R1" H 6909 2896 50  0000 L CNN
F 1 "1k" H 6909 2805 50  0000 L CNN
F 2 "Resistor_SMD:R_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 6850 2850 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1810301711_KOA-Speer-Elec-RK73B2ATTD102J_C159911.pdf" H 6850 2850 50  0001 C CNN
F 4 "lcsc.com" H 6850 2850 50  0001 C CNN "Distributor"
F 5 "RK73B2ATTD102J" H 6850 2850 50  0001 C CNN "Manuf. Part"
	1    6850 2850
	1    0    0    -1  
$EndComp
Wire Wire Line
	6600 2250 7150 2250
Wire Wire Line
	6600 2150 6950 2150
Wire Wire Line
	6950 2050 6950 2150
Wire Wire Line
	6950 2050 7150 2050
Wire Wire Line
	7300 2150 7300 2250
Wire Wire Line
	7250 2150 7300 2150
$Comp
L power:GND #PWR0104
U 1 1 5CBB96C3
P 7300 2250
F 0 "#PWR0104" H 7300 2000 50  0001 C CNN
F 1 "GND" H 7305 2077 50  0000 C CNN
F 2 "" H 7300 2250 50  0001 C CNN
F 3 "" H 7300 2250 50  0001 C CNN
	1    7300 2250
	1    0    0    -1  
$EndComp
$Comp
L blueled-rescue:RESON-MURATA-CSTCE-pasv-xtal X1
U 1 1 5CBDC71D
P 7150 2150
F 0 "X1" H 6950 1950 50  0000 L CNN
F 1 "RESON-MURATA-CSTCE" H 6200 2050 50  0000 L CNN
F 2 "blueled:Resonator_SMD_muRata_CSTNE_3Pin_3.2x1.3mm" H 7150 2000 60  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1912111437_Murata-Electronics-CSTNE8M00G55Z000R0_C341524.pdf" H 7150 2150 60  0001 C CNN
F 4 "lcsc.com" H 7150 2150 50  0001 C CNN "Distributor"
F 5 "CSTNE8M00G55Z000R0" H 7150 2150 50  0001 C CNN "Manuf. Part"
	1    7150 2150
	-1   0    0    1   
$EndComp
Wire Wire Line
	6850 3050 7200 3050
Connection ~ 6850 3050
NoConn ~ 6600 1750
$Comp
L blueled-rescue:MOUDLE-BLUETOOTH-HC-05(34P-27X13MM)-MOUDLE-BLUETOOTH-HC-05_34P-27X13MM_ U2
U 1 1 5CB7CCE4
P 3200 5850
F 0 "U2" H 3200 6767 50  0000 C CNN
F 1 "HC-05" H 3200 6676 50  0000 C CNN
F 2 "MOUDLE-BLUETOOTH-HC-05_34P-27X13MM_:BT34P-SMD-1.5-26.9X13.0X2.2MM" H 3200 5850 50  0001 L BNN
F 3 "https://components101.com/sites/default/files/component_datasheet/HC-05%20Datasheet.pdf" H 3200 5850 50  0001 L BNN
F 4 "Unavailable" H 3200 5850 50  0001 L BNN "Field4"
F 5 "SOIC-14" H 3200 5850 50  0001 L BNN "Field6"
F 6 "HuiCheng" H 3200 5850 50  0001 L BNN "Field7"
F 7 "None" H 3200 5850 50  0001 L BNN "Field8"
F 8 "aliexpress.com" H 3200 5850 50  0001 C CNN "Distributor"
	1    3200 5850
	1    0    0    -1  
$EndComp
Text Label 1900 6200 2    50   ~ 0
HC-RESET
Wire Wire Line
	1900 6200 2100 6200
Text Label 6700 3850 0    50   ~ 0
HC-RESET
Wire Wire Line
	6600 3850 6700 3850
$Comp
L Device:C C1
U 1 1 5EAA33DA
P 2600 1350
F 0 "C1" H 2400 1400 50  0000 L CNN
F 1 "10uF" H 2300 1300 50  0000 L CNN
F 2 "Capacitor_SMD:C_0805_2012Metric_Pad1.15x1.40mm_HandSolder" H 2638 1200 50  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/1810191226_Samsung-Electro-Mechanics-CL21A106MQFNNNE_C41893.pdf" H 2600 1350 50  0001 C CNN
F 4 "lcsc.com" H 2600 1350 50  0001 C CNN "Distributor"
F 5 "CL21A106MQFNNNE" H 2600 1350 50  0001 C CNN "Manuf. Part"
	1    2600 1350
	-1   0    0    1   
$EndComp
Wire Wire Line
	2500 1200 2600 1200
Connection ~ 2600 1200
Wire Wire Line
	2600 1200 2850 1200
Wire Wire Line
	1600 1400 1600 1200
Wire Wire Line
	1700 1400 1600 1400
NoConn ~ 1700 1900
NoConn ~ 2100 1800
Wire Wire Line
	1600 1600 1700 1600
Wire Wire Line
	1600 1650 1600 1600
$Comp
L power:GND #PWR0110
U 1 1 5D474D63
P 1600 1650
F 0 "#PWR0110" H 1600 1400 50  0001 C CNN
F 1 "GND" H 1605 1477 50  0000 C CNN
F 2 "" H 1600 1650 50  0001 C CNN
F 3 "" H 1600 1650 50  0001 C CNN
	1    1600 1650
	1    0    0    -1  
$EndComp
NoConn ~ 1700 1700
$Comp
L SparkFun-Switches:SWITCH-DPDT-PTH-GPI-152-3013 S1
U 1 1 5EB8E526
P 1900 1700
F 0 "S1" H 1900 2176 45  0000 C CNN
F 1 "SWITCH-DPDT-PTH-GPI-152-3013" H 1900 2176 45  0001 C CNN
F 2 "blueled:XKB7070-X" H 1900 2150 20  0001 C CNN
F 3 "https://datasheet.lcsc.com/szlcsc/2002271810_XKB-Enterprise-XKB7070-Z_C318863.pdf" H 1900 1700 50  0001 C CNN
F 4 "SWCH-10554" H 1900 2081 60  0000 C CNN "Field4"
F 5 "lcsc.com" H 1900 1700 50  0001 C CNN "Distributor"
F 6 "XKB7070-Z" H 1900 1700 50  0001 C CNN "Manuf. Part"
	1    1900 1700
	-1   0    0    1   
$EndComp
Wire Wire Line
	2100 1500 2300 1500
Wire Wire Line
	5250 1850 5250 2050
Wire Wire Line
	5250 1550 5250 1150
Wire Wire Line
	5250 1150 6000 1150
Connection ~ 5250 1550
$EndSCHEMATC
