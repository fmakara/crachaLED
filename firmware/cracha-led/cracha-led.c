/*
 * cracha_led.c
 *
 * Created: 27/08/2012 18:26:13
 *  Author: Felipe
 * Pinagem Colunas (normal baixo):
 *	PC2  PC0  PB4  PB2  PD3  PB6  PD5  PD7
 * Pinagem Verde (normal alto):
 *  PB0  PD6  PB7  PD4  PB1  PB3  PB5  PC1
 * Bot�o Modo: PC5
 * Porta Serial: PD0  PD1
 */ 
#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>
#include <avr/interrupt.h>
#include <avr/pgmspace.h>
/*
01 - Paula
02 - Andressa
04 - Pietro
05 - Diogo
06 - Augusto
07 - Tiago
08 - Victor
09 - Paulo G.
10 - Guilherme
11 - Gisele
12 - Paulo H.
13 - Andressa
14 - Raphael
15 - Jagher
16 - Carol
17 - Natasha
18 - Leila
19 - Giovanna
20 - Jos� Lucas
21 - Stephanni
22 - Sarah
23 - Paix�o
24 - Ewaldo Mehl
25 - Alessandro Zimmer
26 - Waldomiro Yuan
27 - James Baraniuk
28 - Luiz Lolis
29 - Edson Pacheco
*/
char BUFFER[256];
char POSICAO;
char SEQUENCIA;
char NEXTB, NEXTC, NEXTD;

#define NUM_PESSOAS 15

const unsigned char NOMES[NUM_PESSOAS][256] PROGMEM = {
	//Eletrica
	{0,128,192,216,248,252,252,124,126,62,62,54,23,7,3,3,1,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,254,1,1,1,1,254,0,255,144,144,144,128,0,255,136,136,136,112,0,255,144,144,152,150,97,0,0,1,3,3,7,23,54,62,62,126,124,252,252,248,216,192,128,0,0,0,0,255,255,255,0,0,248,248,248,0,0,219,219,219,219,219,219,219,0,0,192,192,192,223,223,192,192,192,0,0,0,0,0,0,0,254,1,1,1,1,254,0,255,144,144,144,128,0,255,136,136,136,112,0,255,144,144,152,150,97,0,0,0,0,32,64,255,0,0,0,126,129,129,129,126,0,126,129,129,129,126,0,0,0,0,3,12,116,132,116,12,3,0,255,64,48,12,2,255,0,60,66,129,129,129,66,60,0,98,145,145,137,137,70,0,0,0,0,0},
	//Makara
	{255,144,144,144,128,0,255,145,145,145,145,0,255,1,1,1,1,0,255,0,255,136,136,136,112,0,255,145,145,145,145,0,0,0,0,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,255,255,255,0,0,248,248,248,0,0,219,219,219,219,219,219,219,0,0,192,192,192,223,223,192,192,192,0,0,0,0,0,0,0,255,144,144,144,128,0,255,145,145,145,145,0,255,1,1,1,1,0,255,0,255,136,136,136,112,0,255,145,145,145,145,0,0,0,0,0,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,255,255,255,0,0,248,248,248,0,0,219,219,219,219,219,219,219,0,0,192,192,192,223,223,192,192,192,0,0,0,0,0},
	//Andressa
	//{0,0,3,12,116,132,116,12,3,0,255,64,48,12,2,255,0,255,129,129,129,66,60,0,255,144,144,152,150,97,0,255,145,145,145,145,0,98,145,145,137,137,70,0,98,145,145,137,137,70,0,3,12,116,132,116,12,3,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,3,12,116,132,116,12,3,0,255,64,48,12,2,255,0,255,129,129,129,66,60,0,255,144,144,152,150,97,0,255,145,145,145,145,0,98,145,145,137,137,70,0,98,145,145,137,137,70,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0},
	//pietro
	//{0,0,0,255,136,136,136,112,0,255,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,60,66,129,129,129,66,60,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,136,136,136,112,0,255,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,60,66,129,129,129,66,60,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//diogo
	//{0,0,255,129,129,129,66,60,0,255,0,60,66,129,129,129,66,60,0,60,66,129,129,137,74,44,0,60,66,129,129,129,66,60,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,129,129,129,66,60,0,255,0,60,66,129,129,129,66,60,0,60,66,129,129,137,74,44,0,60,66,129,129,129,66,60,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//gisele
	{0,0,60,66,129,129,137,74,44,0,255,0,98,145,145,137,137,70,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,60,66,129,129,137,74,44,0,255,0,98,145,145,137,137,70,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//paulo h dael
	//{0,0,255,136,136,136,112,0,3,12,116,132,116,12,3,0,254,1,1,1,1,254,0,255,1,1,1,1,0,60,66,129,129,129,66,60,0,0,0,0,255,16,16,16,16,255,0,0,1,0,0,0,0,0,0,0,255,129,129,129,66,60,0,3,12,116,132,116,12,3,0,255,145,145,145,145,0,255,1,1,1,1,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,136,136,136,112,0,3,12,116,132,116,12,3,0,254,1,1,1,1,254,0,255,1,1,1,1,0,60,66,129,129,129,66,60,0,0,0,0,255,16,16,16,16,255,0,0,1,0,0,0,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0},
	//andressa dael
	{0,3,12,116,132,116,12,3,0,255,64,48,12,2,255,0,255,129,129,129,66,60,0,255,144,144,152,150,97,0,255,145,145,145,145,0,98,145,145,137,137,70,0,98,145,145,137,137,70,0,3,12,116,132,116,12,3,0,0,0,0,255,129,129,129,66,60,0,3,12,116,132,116,12,3,0,255,145,145,145,145,0,255,1,1,1,1,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,12,116,132,116,12,3,0,255,64,48,12,2,255,0,255,129,129,129,66,60,0,255,144,144,152,150,97,0,255,145,145,145,145,0,98,145,145,137,137,70,0,98,145,145,137,137,70,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,255,129,129,129,66,60,0,3,12,116,132,116,12,3,0,255,145,145,145,145,0,255,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//ewaldo
	{255,145,145,145,145,192,60,3,12,112,128,112,12,3,60,192,3,12,116,132,116,12,3,0,255,1,1,1,1,0,255,129,129,129,66,60,0,60,66,129,129,129,66,60,0,0,0,0,255,96,28,3,28,96,255,0,255,145,145,145,145,0,255,16,16,16,16,255,0,255,1,1,1,1,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,255,145,145,145,145,192,60,3,12,112,128,112,12,3,60,192,3,12,116,132,116,12,3,0,255,1,1,1,1,0,255,129,129,129,66,60,0,60,66,129,129,129,66,60,0,0,0,0,255,96,28,3,28,96,255,0,255,145,145,145,145,0,255,16,16,16,16,255,0,255,1,1,1,1,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0},
	//zimmer
	//{0,63,18,33,33,30,0,63,16,32,0,30,33,33,33,30,0,32,127,160,0,0,0,0,1,131,141,177,193,129,0,255,0,255,96,28,3,28,96,255,0,255,96,28,3,28,96,255,0,255,145,145,145,145,0,255,144,144,152,150,97,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,63,18,33,33,30,0,63,16,32,0,30,33,33,33,30,0,32,127,160,0,0,0,0,1,131,141,177,193,129,0,255,0,255,96,28,3,28,96,255,0,255,96,28,3,28,96,255,0,255,145,145,145,145,0,255,144,144,152,150,97,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//paula
	{0,0,255,136,136,136,112,0,3,12,116,132,116,12,3,0,254,1,1,1,1,254,0,255,1,1,1,1,0,3,12,116,132,116,12,3,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,136,136,136,112,0,3,12,116,132,116,12,3,0,254,1,1,1,1,254,0,255,1,1,1,1,0,3,12,116,132,116,12,3,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//augusto
	//{0,128,192,216,248,252,252,124,126,62,62,54,23,7,3,3,1,0,0,0,0,3,12,116,132,116,12,3,0,254,1,1,1,1,254,0,60,66,129,129,137,74,44,0,254,1,1,1,1,254,0,98,145,145,137,137,70,0,128,128,255,128,128,0,60,66,129,129,129,66,60,0,0,0,0,0,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,1,3,3,7,23,54,62,62,126,124,252,252,248,216,192,128,0,0,0,0,0,0,0,0,0,0,0,0,0,0,128,192,216,248,252,252,124,126,62,62,54,23,7,3,3,1,0,0,0,0,0,255,255,255,0,0,248,248,248,0,0,219,219,219,219,219,219,219,0,0,192,192,192,223,223,192,192,192,0,0,1,3,3,7,23,54,62,62,126,124,252,252,248,216,192,128,0,0,0,0,0,0,0,0},
	//tiago
	//{0,128,192,216,248,252,252,252,254,126,126,62,23,7,3,3,1,0,192,128,129,255,129,128,192,0,129,255,129,0,1,7,61,196,61,7,1,60,66,129,137,137,206,0,60,66,129,129,129,66,60,0,0,0,8,8,8,0,0,0,0,255,255,255,0,248,248,248,0,0,219,219,219,219,219,219,219,0,0,192,192,192,223,223,192,192,192,0,1,3,3,7,23,62,126,126,254,252,252,252,248,216,192,128,0,0,0,0,0,0,0,192,128,129,255,129,128,192,0,129,255,129,0,1,7,61,196,61,7,1,60,66,129,137,137,206,0,60,66,129,129,129,66,60,0,0,0,0,0,0,0,0,0,128,192,216,248,252,252,252,254,126,126,62,23,7,3,3,1,0,192,128,129,255,129,128,192,0,129,255,129,0,1,7,61,196,61,7,1,60,66,129,137,137,206,0,60,66,129,129,129,66,60,0,0,0,8,8,8,0,0,0,0,255,255,255,0,248,248,248,0,0,219,219,219,219,219,219,219,0,0,192,192,192,223,223,192,192,192,0,1,3,3,7,23,62,126,126,254,252,252,252,248,216,192,128},
	//raphael dael
	{255,144,144,152,150,97,0,3,12,116,132,116,12,3,0,255,136,136,136,112,0,255,16,16,16,16,255,0,3,12,116,132,116,12,3,0,255,145,145,145,145,0,255,1,1,1,1,0,0,0,0,255,129,129,129,66,60,0,3,12,116,132,116,12,3,0,255,145,145,145,145,0,255,1,1,1,1,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,144,144,152,150,97,0,3,12,116,132,116,12,3,0,255,136,136,136,112,0,255,16,16,16,16,255,0,3,12,116,132,116,12,3,0,255,145,145,145,145,0,255,1,1,1,1,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//giovanna
	//{60,66,129,129,137,74,44,0,255,0,60,66,129,129,129,66,60,0,192,48,12,3,12,48,192,0,3,12,116,132,116,12,3,0,255,64,48,12,2,255,0,255,64,48,12,2,255,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,60,66,129,129,137,74,44,0,255,0,60,66,129,129,129,66,60,0,192,48,12,3,12,48,192,0,3,12,116,132,116,12,3,0,255,64,48,12,2,255,0,255,64,48,12,2,255,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//jose
	//{6,1,1,254,0,60,66,129,129,129,66,60,0,98,145,145,137,137,70,0,255,145,145,145,145,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,6,1,1,254,0,60,66,129,129,129,66,60,0,98,145,145,137,137,70,0,255,145,145,145,145,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,6,1,1,254,0,60,66,129,129,129,66,60,0,98,145,145,137,137,70,0,255,145,145,145,145,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0},
	//victor
	{192,48,12,3,12,48,192,0,255,0,60,66,129,129,129,66,0,128,128,255,128,128,0,60,66,129,129,129,66,60,0,255,144,144,152,150,97,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,192,48,12,3,12,48,192,0,255,0,60,66,129,129,129,66,0,128,128,255,128,128,0,60,66,129,129,129,66,60,0,255,144,144,152,150,97,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//paulo
	{255,136,136,136,112,0,3,12,116,132,116,12,3,0,254,1,1,1,1,254,0,255,1,1,1,1,0,60,66,129,129,129,66,60,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,136,136,136,112,0,3,12,116,132,116,12,3,0,254,1,1,1,1,254,0,255,1,1,1,1,0,60,66,129,129,129,66,60,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//guilherme
	{60,66,129,129,137,74,44,0,254,1,1,1,1,254,0,255,0,255,1,1,1,1,0,255,16,16,16,16,255,0,255,145,145,145,145,0,255,144,144,152,150,97,0,255,96,28,3,28,96,255,0,255,145,145,145,145,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,12,116,132,116,12,3,0,192,48,12,3,12,48,192,0,3,12,116,132,116,12,3,0,255,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//jagher
	{255,145,145,145,145,0,255,129,129,129,66,60,0,254,1,1,1,1,254,0,3,12,116,132,116,12,3,0,255,144,144,152,150,97,0,255,129,129,129,66,60,0,60,66,129,129,129,66,60,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,255,145,145,145,145,0,255,129,129,129,66,60,0,254,1,1,1,1,254,0,3,12,116,132,116,12,3,0,255,144,144,152,150,97,0,255,129,129,129,66,60,0,60,66,129,129,129,66,60,0,0,0,0,255,136,136,136,112,0,255,145,145,145,145,0,128,128,255,128,128,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0},
	//james
	{255,72,132,132,120,0,63,16,32,0,30,33,33,33,30,0,32,127,160,0,0,0,0,6,1,1,254,0,3,12,116,132,116,12,3,0,255,96,28,3,28,96,255,0,255,145,145,145,145,0,98,145,145,137,137,70,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,72,132,132,120,0,63,16,32,0,30,33,33,33,30,0,32,127,160,0,0,0,0,6,1,1,254,0,3,12,116,132,116,12,3,0,255,96,28,3,28,96,255,0,255,145,145,145,145,0,98,145,145,137,137,70,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//luiz
	{255,136,136,136,112,0,63,16,32,0,30,33,33,33,30,0,32,127,160,0,0,0,0,255,1,1,1,1,0,254,1,1,1,1,254,0,255,0,1,131,141,177,193,129,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,255,136,136,136,112,0,63,16,32,0,30,33,33,33,30,0,32,127,160,0,0,0,0,255,1,1,1,1,0,254,1,1,1,1,254,0,255,0,1,131,141,177,193,129,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
	//pacheco
	{255,136,136,136,112,0,63,16,32,0,30,33,33,33,30,0,32,127,160,0,0,0,0,255,136,136,136,112,0,3,12,116,132,116,12,3,0,60,66,129,129,129,66,0,255,16,16,16,16,255,0,255,145,145,145,145,0,60,66,129,129,129,66,0,60,66,129,129,129,66,60,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,255,136,136,136,112,0,63,16,32,0,30,33,33,33,30,0,32,127,160,0,0,0,0,255,136,136,136,112,0,3,12,116,132,116,12,3,0,60,66,129,129,129,66,0,255,16,16,16,16,255,0,255,145,145,145,145,0,60,66,129,129,129,66,0,60,66,129,129,129,66,60,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0},
	//mariano
	{255,136,136,136,112,0,63,16,32,0,30,33,33,33,30,0,32,127,160,0,0,0,0,255,96,28,3,28,96,255,0,3,12,116,132,116,12,3,0,255,144,144,152,150,97,0,255,0,3,12,116,132,116,12,3,0,255,64,48,12,2,255,0,60,66,129,129,129,66,60,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0,255,136,136,136,112,0,63,16,32,0,30,33,33,33,30,0,32,127,160,0,0,0,0,255,96,28,3,28,96,255,0,3,12,116,132,116,12,3,0,255,144,144,152,150,97,0,255,0,3,12,116,132,116,12,3,0,255,64,48,12,2,255,0,60,66,129,129,129,66,60,0,0,0,0,255,145,145,145,145,0,255,1,1,1,1,0,255,145,145,145,145,0,128,128,255,128,128,0,255,144,144,152,150,97,0,255,0,60,66,129,129,129,66,0,3,12,116,132,116,12,3,0,0,0,0,0,0,0},
};

void delay(char cem){
	while(cem>0){
		cem--;
		_delay_ms(100);
	}		
}	
int main(void){
	int a, b;
	DDRB = 0b11111111;
	DDRC = 0b11011111;
	DDRD = 0b11111110;
	
	POSICAO = 0;
	SEQUENCIA = 0;

	NEXTB = 0b10101011;
	NEXTC = 0b00000010;
	NEXTD = 0b01010000;//todos apagados
	
	PORTB = 0b10101011 & 0b11111101;
	PORTC = 0b00000010;
	PORTD = 0b01010000 | 0b00001000;
	/*while(1){
		for(b=0;b<8;b++){
			for(a=0;a<128;a = a<<1){
				_delay_ms(100);
				NEXTB = 0b10101011;
				NEXTC = 0b00000010;
				NEXTD = 0b01010000;
				switch(b){//PB0  PD6  PB7  PD4  PB1  PB3  PB5  PC1
					case 0:NEXTC&=0b11111101;break;
					case 1:NEXTB&=0b11011111;break;
					case 2:NEXTB&=0b11110111;break;
					case 3:NEXTB&=0b11111101;break;
					case 4:NEXTD&=0b11101111;break;
					case 5:NEXTB&=0b01111111;break;
					case 6:NEXTD&=0b10111111;break;
					case 7:NEXTB&=0b11111110;break;
				}
				//PC2  PC0  PB4  PB2  PD3  PB6  PD5  PD7
				if(a&1  )NEXTD|=0b10000000;
				if(a&2  )NEXTD|=0b00100000;
				if(a&4  )NEXTB|=0b01000000;
				if(a&8  )NEXTD|=0b00001000;
				if(a&16 )NEXTB|=0b00000100;
				if(a&32 )NEXTB|=0b00010000;
				if(a&64 )NEXTC|=0b00000001;
				if(a&128)NEXTC|=0b00000100;
				PORTB = NEXTB;
				PORTC = NEXTC;
				PORTD = NEXTD;
			}
		}
	}	*/
	
	
	a = eeprom_read_byte((uint8_t *)0);
	if(a>=NUM_PESSOAS)a=0;
	if((PINC&0b00100000)==0){//muda a pessoa
		a++;
		if(a>=NUM_PESSOAS)a=0;
		eeprom_write_byte((uint8_t*)0, a);
	}
	for(b=0;b<256;b++){
		BUFFER[b] = pgm_read_byte(&(NOMES[(unsigned)a][(unsigned)b]));
	}
	PORTB = 0b01111111;
	PORTC = 0b00000111;
	PORTD = 0b11111000;
	TCCR0B = 0b00000011;//SRC = CLK/64 //TCCR0 para atmega8
	TCNT0 = 0;
	TIMSK0 = 0b00000001; //TIMSK para atmega8
	sei();
	while(1){
		_delay_ms(1);
	}
}
ISR(TIMER0_OVF_vect){
	char a, b;
	PORTB = NEXTB;
	PORTC = NEXTC;
	PORTD = NEXTD;
	TCNT0 = 200;
	NEXTB = 0b10101011;
	NEXTC = 0b00000010;
	NEXTD = 0b01010000;//todos apagados
	b = SEQUENCIA%8;
	a = BUFFER[(POSICAO+b)&255];
	switch(b){//PB0  PD6  PB7  PD4  PB1  PB3  PB5  PC1
		case 0:NEXTC&=0b11111101;break;
		case 1:NEXTB&=0b11011111;break;
		case 2:NEXTB&=0b11110111;break;
		case 3:NEXTB&=0b11111101;break;
		case 4:NEXTD&=0b11101111;break;
		case 5:NEXTB&=0b01111111;break;
		case 6:NEXTD&=0b10111111;break;
		case 7:NEXTB&=0b11111110;break;
	}
	//PC2  PC0  PB4  PB2  PD3  PB6  PD5  PD7
	if(a&1  )NEXTD|=0b10000000;
	if(a&2  )NEXTD|=0b00100000;
	if(a&4  )NEXTB|=0b01000000;
	if(a&8  )NEXTD|=0b00001000;
	if(a&16 )NEXTB|=0b00000100;
	if(a&32 )NEXTB|=0b00010000;
	if(a&64 )NEXTC|=0b00000001;
	if(a&128)NEXTC|=0b00000100;
	SEQUENCIA++;
	if(SEQUENCIA==0)POSICAO++;
}