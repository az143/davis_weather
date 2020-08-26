EESchema Schematic File Version 4
EELAYER 26 0
EELAYER END
$Descr A4 11693 8268
encoding utf-8
Sheet 1 1
Title "notdavis"
Date "2020-08-08"
Rev "2.0"
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
$Comp
L Device:C_Small C1
U 1 1 5F2E57C1
P 2750 5450
F 0 "C1" H 2842 5496 50  0000 L CNN
F 1 "0.1µF" H 2842 5405 50  0000 L CNN
F 2 "Capacitor_THT:C_Rect_L7.0mm_W3.5mm_P5.00mm" H 2750 5450 50  0001 C CNN
F 3 "~" H 2750 5450 50  0001 C CNN
	1    2750 5450
	1    0    0    -1  
$EndComp
$Comp
L SparkFun-Connectors:CONN_02JST-PTH-2 J2
U 1 1 5F2E5989
P 3100 6100
F 0 "J2" H 2872 6192 45  0000 R CNN
F 1 "powervantage" H 2872 6108 45  0000 R CNN
F 2 "Connector_JST:JST_XH_B02B-XH-A_1x02_P2.50mm_Vertical" H 3100 6400 20  0001 C CNN
F 3 "" H 3100 6100 50  0001 C CNN
	1    3100 6100
	1    0    0    1   
$EndComp
$Comp
L SparkFun-Connectors:CONN_04JST-PTH-VERT J3
U 1 1 5F2E5B1D
P 4050 5900
F 0 "J3" H 3823 6092 45  0000 R CNN
F 1 "bbb" H 3823 6008 45  0000 R CNN
F 2 "Connector_JST:JST_XH_S04B-XH-A_1x04_P2.50mm_Horizontal" H 4050 6400 20  0001 C CNN
F 3 "" H 4050 5900 50  0001 C CNN
	1    4050 5900
	-1   0    0    1   
$EndComp
$Comp
L Connector_Generic:Conn_02x10_Odd_Even J1
U 1 1 5F2E679A
P 1950 4900
F 0 "J1" H 2000 5517 50  0000 C CNN
F 1 "vantage" H 2000 5426 50  0000 C CNN
F 2 "Connector_PinSocket_2.00mm:PinSocket_2x10_P2.00mm_Vertical_SMD" H 1950 4900 50  0001 C CNN
F 3 "~" H 1950 4900 50  0001 C CNN
	1    1950 4900
	1    0    0    -1  
$EndComp
$Comp
L dk_Embedded-Microcontrollers:PIC12F675-I_P U1
U 1 1 5F2E6B45
P 4200 4850
F 0 "U1" H 4828 4803 60  0000 L CNN
F 1 "pic16f18313" H 4828 4697 60  0000 L CNN
F 2 "Package_DIP:DIP-8_W7.62mm" H 4400 5050 60  0001 L CNN
F 3 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en011653" H 4400 5150 60  0001 L CNN
F 4 "PIC12F675-I/P-ND" H 4400 5250 60  0001 L CNN "Digi-Key_PN"
F 5 "PIC12F675-I/P" H 4400 5350 60  0001 L CNN "MPN"
F 6 "Integrated Circuits (ICs)" H 4400 5450 60  0001 L CNN "Category"
F 7 "Embedded - Microcontrollers" H 4400 5550 60  0001 L CNN "Family"
F 8 "http://www.microchip.com/mymicrochip/filehandler.aspx?ddocname=en011653" H 4400 5650 60  0001 L CNN "DK_Datasheet_Link"
F 9 "/product-detail/en/microchip-technology/PIC12F675-I-P/PIC12F675-I-P-ND/459171" H 4400 5750 60  0001 L CNN "DK_Detail_Page"
F 10 "IC MCU 8BIT 1.75KB FLASH 8DIP" H 4400 5850 60  0001 L CNN "Description"
F 11 "Microchip Technology" H 4400 5950 60  0001 L CNN "Manufacturer"
F 12 "Active" H 4400 6050 60  0001 L CNN "Status"
	1    4200 4850
	1    0    0    -1  
$EndComp
Wire Wire Line
	2550 4350 2550 5100
Wire Wire Line
	2550 5100 2250 5100
Wire Wire Line
	4500 5550 2750 5550
Wire Wire Line
	2550 5550 2550 5200
Wire Wire Line
	2550 5200 2250 5200
Connection ~ 2750 5550
Wire Wire Line
	2750 5550 2550 5550
Wire Wire Line
	2550 5100 2750 5100
Wire Wire Line
	2750 5100 2750 5350
Connection ~ 2550 5100
Wire Wire Line
	2550 4350 4500 4350
Wire Wire Line
	3200 6100 3500 6100
$Comp
L power:GND #PWR03
U 1 1 5F2E7845
P 3500 6100
F 0 "#PWR03" H 3500 5850 50  0001 C CNN
F 1 "GND" H 3505 5927 50  0000 C CNN
F 2 "" H 3500 6100 50  0001 C CNN
F 3 "" H 3500 6100 50  0001 C CNN
	1    3500 6100
	-1   0    0    1   
$EndComp
Connection ~ 3500 6100
Wire Wire Line
	3500 6100 3950 6100
$Comp
L power:GND #PWR02
U 1 1 5F2E788D
P 2550 5550
F 0 "#PWR02" H 2550 5300 50  0001 C CNN
F 1 "GND" H 2555 5377 50  0000 C CNN
F 2 "" H 2550 5550 50  0001 C CNN
F 3 "" H 2550 5550 50  0001 C CNN
	1    2550 5550
	1    0    0    -1  
$EndComp
Connection ~ 2550 5550
Text GLabel 1400 4600 0    50   Input ~ 0
miso
Text GLabel 1650 4500 0    50   Input ~ 0
ck
Text GLabel 2350 4500 2    50   Input ~ 0
ss
Text GLabel 2350 4600 2    50   Input ~ 0
mosi
Wire Wire Line
	3900 4650 2750 4650
Wire Wire Line
	2750 4650 2750 4000
Wire Wire Line
	2750 4000 1400 4000
Wire Wire Line
	1400 4000 1400 4600
Wire Wire Line
	1400 4600 1750 4600
Wire Wire Line
	3900 4750 2850 4750
Wire Wire Line
	2850 4750 2850 4100
Wire Wire Line
	2850 4100 1650 4100
Wire Wire Line
	1650 4100 1650 4500
Wire Wire Line
	1750 4500 1650 4500
Text GLabel 1650 4700 0    50   Input ~ 0
txd
Text GLabel 2350 4700 2    50   Input ~ 0
rxd
Wire Wire Line
	3950 6000 2350 6000
Wire Wire Line
	2350 6000 2350 4700
Wire Wire Line
	2350 4700 2250 4700
Wire Wire Line
	3950 5900 1650 5900
Wire Wire Line
	1650 5900 1650 4700
Wire Wire Line
	1750 4700 1650 4700
Wire Wire Line
	3900 4950 3150 4950
Wire Wire Line
	3150 4950 3150 4500
Wire Wire Line
	3150 4500 2250 4500
Wire Wire Line
	3900 5050 3250 5050
Wire Wire Line
	3250 5050 3250 4600
Wire Wire Line
	3250 4600 2250 4600
$Comp
L power:+3.3V #PWR0102
U 1 1 5F2EB4D1
P 2550 4350
F 0 "#PWR0102" H 2550 4200 50  0001 C CNN
F 1 "+3.3V" H 2565 4523 50  0000 C CNN
F 2 "" H 2550 4350 50  0001 C CNN
F 3 "" H 2550 4350 50  0001 C CNN
	1    2550 4350
	1    0    0    -1  
$EndComp
Connection ~ 2550 4350
Wire Wire Line
	3200 6200 3500 6200
$Comp
L power:+5V #PWR0101
U 1 1 5F2EB965
P 3500 6200
F 0 "#PWR0101" H 3500 6050 50  0001 C CNN
F 1 "+5V" H 3515 6373 50  0000 C CNN
F 2 "" H 3500 6200 50  0001 C CNN
F 3 "" H 3500 6200 50  0001 C CNN
	1    3500 6200
	-1   0    0    1   
$EndComp
Connection ~ 3500 6200
Wire Wire Line
	3500 6200 3950 6200
$EndSCHEMATC
