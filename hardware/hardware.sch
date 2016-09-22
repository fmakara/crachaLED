EESchema Schematic File Version 2  date 29-08-2012 14:20:30
LIBS:power
LIBS:device
LIBS:transistors
LIBS:conn
LIBS:linear
LIBS:regul
LIBS:74xx
LIBS:cmos4000
LIBS:adc-dac
LIBS:memory
LIBS:xilinx
LIBS:special
LIBS:microcontrollers
LIBS:dsp
LIBS:microchip
LIBS:analog_switches
LIBS:motorola
LIBS:texas
LIBS:intel
LIBS:audio
LIBS:interface
LIBS:digital-audio
LIBS:philips
LIBS:display
LIBS:cypress
LIBS:siliconi
LIBS:opto
LIBS:atmel
LIBS:contrib
LIBS:valves
LIBS:hardware-cache
EELAYER 25  0
EELAYER END
$Descr A4 11700 8267
encoding utf-8
Sheet 1 1
Title ""
Date "29 aug 2012"
Rev ""
Comp ""
Comment1 ""
Comment2 ""
Comment3 ""
Comment4 ""
$EndDescr
NoConn ~ 9300 4000
NoConn ~ 9300 3700
NoConn ~ 9300 3400
NoConn ~ 9300 3100
Wire Wire Line
	9300 3000 9700 3000
Wire Wire Line
	9700 3000 9700 4600
Wire Wire Line
	9700 4600 5050 4600
Wire Wire Line
	9300 3300 9600 3300
Wire Wire Line
	9600 3300 9600 4500
Wire Wire Line
	9600 4500 5150 4500
Wire Wire Line
	9300 3600 9500 3600
Wire Wire Line
	9500 3600 9500 4400
Wire Wire Line
	9500 4400 5250 4400
Wire Wire Line
	9300 3900 9400 3900
Wire Wire Line
	9400 3900 9400 4300
Wire Wire Line
	9400 4300 5350 4300
Wire Wire Line
	6800 3100 7450 3100
Wire Wire Line
	7450 3100 7450 3000
Wire Wire Line
	7450 3000 7500 3000
Wire Wire Line
	7500 3300 6800 3300
Wire Wire Line
	7500 3600 7350 3600
Wire Wire Line
	7350 3600 7350 3800
Wire Wire Line
	7350 3800 6800 3800
Wire Wire Line
	7500 3900 7450 3900
Wire Wire Line
	7450 3900 7450 4000
Wire Wire Line
	7450 4000 6800 4000
Wire Wire Line
	6850 3450 6850 3400
Wire Wire Line
	6850 3400 6800 3400
Wire Wire Line
	4200 3200 4950 3200
Wire Wire Line
	4950 3200 4950 2900
Wire Wire Line
	5800 2300 5500 2300
Wire Wire Line
	5600 1900 5600 1800
Wire Wire Line
	5400 2200 5500 2200
Wire Wire Line
	5500 2200 5500 2300
Wire Wire Line
	5400 3000 5000 3000
Wire Wire Line
	5200 3450 5200 3400
Wire Wire Line
	6250 2450 6250 2550
Wire Wire Line
	6800 2800 6800 2550
Wire Wire Line
	5200 3400 5400 3400
Connection ~ 5200 2800
Wire Wire Line
	5100 2800 5400 2800
Wire Wire Line
	5400 3300 5100 3300
Wire Wire Line
	5100 3300 5100 4550
Wire Wire Line
	5400 3700 5200 3700
Wire Wire Line
	5200 3700 5200 4450
Wire Wire Line
	5400 3900 5300 3900
Wire Wire Line
	5300 3900 5300 4350
Wire Wire Line
	5400 4100 5400 4250
Wire Wire Line
	5400 4000 5350 4000
Wire Wire Line
	5350 4000 5350 4300
Wire Wire Line
	5400 3800 5250 3800
Wire Wire Line
	5250 3800 5250 4400
Wire Wire Line
	5400 3600 5150 3600
Wire Wire Line
	5150 3600 5150 4500
Wire Wire Line
	5400 3200 5050 3200
Wire Wire Line
	5050 3200 5050 4600
Wire Wire Line
	5200 2800 5200 2900
Wire Wire Line
	4500 2900 4500 2800
Wire Wire Line
	6800 2550 6750 2550
Wire Wire Line
	7400 2550 7400 2650
Connection ~ 6800 2550
Wire Wire Line
	4950 2900 5400 2900
Wire Wire Line
	4200 3000 4350 3000
Wire Wire Line
	4350 3000 4350 2800
Wire Wire Line
	4350 2800 4500 2800
Connection ~ 4500 2800
Wire Wire Line
	5400 2000 5500 2000
Wire Wire Line
	5500 2000 5500 1900
Wire Wire Line
	5600 2300 5600 2350
Connection ~ 5600 2300
Connection ~ 5600 1900
Wire Wire Line
	5500 1900 5800 1900
Wire Wire Line
	5000 3000 5000 3100
Wire Wire Line
	5000 3100 4200 3100
Wire Wire Line
	7500 4100 6800 4100
Wire Wire Line
	7500 3800 7400 3800
Wire Wire Line
	7400 3800 7400 3900
Wire Wire Line
	7400 3900 6800 3900
Wire Wire Line
	7500 3500 7300 3500
Wire Wire Line
	7300 3500 7300 3700
Wire Wire Line
	7300 3700 6800 3700
Wire Wire Line
	7500 3200 6800 3200
Wire Wire Line
	5400 4250 9350 4250
Wire Wire Line
	9350 4250 9350 4100
Wire Wire Line
	9350 4100 9300 4100
Wire Wire Line
	9300 3800 9450 3800
Wire Wire Line
	9450 3800 9450 4350
Wire Wire Line
	9450 4350 5300 4350
Wire Wire Line
	9300 3500 9550 3500
Wire Wire Line
	9550 3500 9550 4450
Wire Wire Line
	9550 4450 5200 4450
Wire Wire Line
	9300 3200 9650 3200
Wire Wire Line
	9650 3200 9650 4550
Wire Wire Line
	9650 4550 5100 4550
NoConn ~ 7500 3100
NoConn ~ 7500 3400
NoConn ~ 7500 3700
NoConn ~ 7500 4000
$Comp
L MATRIX_LED U1
U 1 1 503E4D8F
P 8400 3550
F 0 "U1" H 8400 4100 60  0000 C CNN
F 1 "MATRIX_LED" H 8350 3000 60  0000 C CNN
	1    8400 3550
	-1   0    0    -1  
$EndComp
$Comp
L PWR_FLAG #FLG01
U 1 1 503BD4D7
P 5800 2300
F 0 "#FLG01" H 5800 2395 30  0001 C CNN
F 1 "PWR_FLAG" H 5800 2480 30  0000 C CNN
	1    5800 2300
	0    1    1    0   
$EndComp
$Comp
L PWR_FLAG #FLG02
U 1 1 503BD4D2
P 5800 1900
F 0 "#FLG02" H 5800 1995 30  0001 C CNN
F 1 "PWR_FLAG" H 5800 2080 30  0000 C CNN
	1    5800 1900
	0    1    1    0   
$EndComp
$Comp
L VCC #PWR03
U 1 1 503BD49D
P 5600 1800
F 0 "#PWR03" H 5600 1900 30  0001 C CNN
F 1 "VCC" H 5600 1900 30  0000 C CNN
	1    5600 1800
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR04
U 1 1 503BD499
P 5600 2350
F 0 "#PWR04" H 5600 2350 30  0001 C CNN
F 1 "GND" H 5600 2280 30  0001 C CNN
	1    5600 2350
	1    0    0    -1  
$EndComp
$Comp
L C C1
U 1 1 503BD484
P 5600 2100
F 0 "C1" H 5650 2200 50  0000 L CNN
F 1 "C" H 5650 2000 50  0000 L CNN
	1    5600 2100
	1    0    0    -1  
$EndComp
$Comp
L CONN_2 P1
U 1 1 503BD47B
P 5050 2100
F 0 "P1" V 5000 2100 40  0000 C CNN
F 1 "CONN_2" V 5100 2100 40  0000 C CNN
	1    5050 2100
	-1   0    0    1   
$EndComp
$Comp
L CONN_3 K1
U 1 1 503BD447
P 3850 3100
F 0 "K1" V 3800 3100 50  0000 C CNN
F 1 "CONN_3" V 3900 3100 40  0000 C CNN
	1    3850 3100
	-1   0    0    1   
$EndComp
NoConn ~ 5400 3100
$Comp
L VCC #PWR05
U 1 1 503BD420
P 5200 3450
F 0 "#PWR05" H 5200 3550 30  0001 C CNN
F 1 "VCC" H 5200 3550 30  0000 C CNN
	1    5200 3450
	-1   0    0    1   
$EndComp
$Comp
L GND #PWR06
U 1 1 503BD41D
P 5400 3500
F 0 "#PWR06" H 5400 3500 30  0001 C CNN
F 1 "GND" H 5400 3430 30  0001 C CNN
	1    5400 3500
	1    0    0    -1  
$EndComp
$Comp
L GND #PWR07
U 1 1 503BD419
P 6850 3450
F 0 "#PWR07" H 6850 3450 30  0001 C CNN
F 1 "GND" H 6850 3380 30  0001 C CNN
	1    6850 3450
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR08
U 1 1 503BD406
P 6800 3600
F 0 "#PWR08" H 6800 3700 30  0001 C CNN
F 1 "VCC" H 6800 3700 30  0000 C CNN
	1    6800 3600
	0    1    1    0   
$EndComp
$Comp
L ATMEGA8A-P IC1
U 1 1 503BC977
P 6300 3600
F 0 "IC1" H 5600 4450 50  0000 L BNN
F 1 "ATMEGA8A-P" H 5900 2950 50  0000 L BNN
F 2 "DIL28" H 5700 2900 50  0001 C CNN
	1    6300 3600
	1    0    0    -1  
$EndComp
$Comp
L VCC #PWR09
U 1 1 503BD3D6
P 6250 2450
F 0 "#PWR09" H 6250 2550 30  0001 C CNN
F 1 "VCC" H 6250 2550 30  0000 C CNN
	1    6250 2450
	1    0    0    -1  
$EndComp
$Comp
L R R2
U 1 1 503BD3C0
P 6500 2550
F 0 "R2" V 6580 2550 50  0000 C CNN
F 1 "10k" V 6500 2550 50  0000 C CNN
	1    6500 2550
	0    -1   -1   0   
$EndComp
$Comp
L GND #PWR010
U 1 1 503BD3B9
P 7400 2650
F 0 "#PWR010" H 7400 2650 30  0001 C CNN
F 1 "GND" H 7400 2580 30  0001 C CNN
	1    7400 2650
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW2
U 1 1 503BD3B4
P 7100 2550
F 0 "SW2" H 7250 2660 50  0000 C CNN
F 1 "SW_PUSH" H 7100 2470 50  0000 C CNN
	1    7100 2550
	1    0    0    -1  
$EndComp
NoConn ~ 6800 3000
NoConn ~ 6800 2900
NoConn ~ 6800 3500
$Comp
L GND #PWR011
U 1 1 503BD2D9
P 4500 2900
F 0 "#PWR011" H 4500 2900 30  0001 C CNN
F 1 "GND" H 4500 2830 30  0001 C CNN
	1    4500 2900
	1    0    0    -1  
$EndComp
$Comp
L SW_PUSH SW1
U 1 1 503BD2CE
P 4800 2800
F 0 "SW1" H 4950 2910 50  0000 C CNN
F 1 "SW_PUSH" H 4800 2720 50  0000 C CNN
	1    4800 2800
	1    0    0    -1  
$EndComp
$Comp
L R R1
U 1 1 503BD21F
P 5200 3150
F 0 "R1" V 5280 3150 50  0000 C CNN
F 1 "10k" V 5200 3150 50  0000 C CNN
	1    5200 3150
	1    0    0    -1  
$EndComp
$EndSCHEMATC
