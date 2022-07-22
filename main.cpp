 // Lab3P1.c
 //
 // Created: 7/8/2019 12:44:04 PM
 // Author : Misha Skarlatov
 
#include <math.h>
#include <stdio.h>
#include <string.h>

#define VAR_B  4250 //3434 //3934
#define VAR_TN 273.15
#define VAR_RN 10000.0 //10000.0


// Lab3P1.c
//
// Created: 1/30/2018 4:04:52 AM
// Author : Eugene Rockey
// Copyright 2018, All Rights Reserved
 
//no includes, no ASF, no libraries
 
const char MS1[] = "\r\nECE-412 ATMega328P Tiny OS";
const char MS2[] = "\r\nby Eugene Rockey Copyright 2018, All Rights Reserved";
const char MS3[] = "\r\nMenu: (L)CD, (A)CD, (E)EPROM, (U)USART\r\n";
const char MS4[] = "\r\nReady: ";
const char MS5[] = "\r\nInvalid Command Try Again...";
const char MS6[] = "Volts\r";
const char MS7[] = "\r\nEnter new baud rate";
const char MS11[] = "\r\n2400(q), 4800(w), 9600(e), 14.4k(r), 19.2k(t), 28.8k(y), 38.4k(u), 57.6k(i), 76.8k(o), 115.2k(p), 230.4k(a), 250k(s), 0.5M(d), 1M(f)\r\n";
const char MS8[] = "\r\nEnter # of data bits. seven (7) or eight (8)\r\n";
const char MS9[] = "\r\nEnter parity bit mode. none (0), even (2), odd (3)\r\n";
const char MS10[] = "\r\nEnter # of stop bits. one-bit (1), two-bit (2)\r\n";
 
 

void LCD_Init(void);			//external Assembly functions
void UART_Init(void);
void UART_Clear(void);
void UART_Get(void);
void UART_Put(void);
void LCD_Write_Data(void);
void LCD_Write_Command(void);
void LCD_Read_Data(void);
void Mega328P_Init(void);
void ADC_Get(void);
void EEPROM_Read(void);
void EEPROM_Write(void);
void USART_Baud1(void);
void USART_Baud2(void);
void USART_Baud3(void);
void USART_Baud4(void);
void USART_Baud5(void);
void USART_Baud6(void);
void USART_Baud7(void);
void USART_Baud8(void);
void USART_Baud9(void);
void USART_Baud10(void);
void USART_Baud11(void);
void USART_Baud12(void);
void USART_Baud13(void);
void USART_Baud14(void);
void USART_Databits(void);
void USART_Parity(void);
void USART_Stopbits(void);

unsigned char ASCII;			//shared I/O variable with Assembly
unsigned char DATA;				//shared internal variable with Assembly
char HADC;						//shared ADC variable with Assembly
char LADC;						//shared ADC variable with Assembly
char high;						//Shared variable with Assembly
char low;						//Shared variable with Assembly

char volts[5];					//string buffer for ADC output
int Acc;						//Accumulator for ADC use

void UART_Puts(const char *str)	//Display a string in the PC Terminal Program
{
	while (*str)
	{
		ASCII = *str++;
		UART_Put();
	}
}

void LCD_Puts(const char *str)	//Display a string on the LCD Module
{
	while (*str)
	{
		DATA = *str++;
		LCD_Write_Data();
	}
}


void Banner(void)				//Display Tiny OS Banner on Terminal
{
	UART_Puts(MS1);
	UART_Puts(MS2);
	UART_Puts(MS4);
}

void HELP(void)						//Display available Tiny OS Commands on Terminal
{
	UART_Puts(MS3);
}


void LCD(void)						//Lite LCD demo
{
	//LCD_Init();
	DATA = 0x34;					//Student Comment Here
	LCD_Write_Command();
	DATA = 0x08;					//Student Comment Here
	LCD_Write_Command();
	DATA = 0x02;					//Student Comment Here
	LCD_Write_Command();
	DATA = 0x06;					//Student Comment Here
	LCD_Write_Command();
	DATA = 0x0f;					//Student Comment Here
	LCD_Write_Command();
	//LCD_Puts("Hello ECE412!");
	//char teamName[16] = {"TEAM 5          "};
	//LCD_Puts("      ----  hftft");
	for(int i = 0; i < 15; i++) {
		LCD_Puts(" ");
		for(int j = 0; j < 5; j++) {
			LCD_Puts("TEAM 5          ");
		}
	}

	/*
	Re-engineer this subroutine to have the LCD endlessly scroll a marquee sign of 
	your Team's name either vertically or horizontally. Any key press should stop
	the scrolling and return execution to the command line in Terminal. User must
	always be able to return to command line.
	*/
}

double current_temp;

void ADC(void)						//Lite Demo of the Analog to Digital Converter
{
	volts[0x1]='.';
	volts[0x3]=' ';
	volts[0x4]= 0;
	ADC_Get();
	double answer;
	Acc = (((int)HADC) * 0x100 + (int)(LADC))*0xA;
	Acc = (int)HADC << 6 | (int)LADC;
	answer =  10000.0 * (double)Acc / (1024.0 - (double)Acc);
	answer = VAR_B * VAR_TN / (VAR_TN * (log(answer/VAR_RN))+VAR_B);
	answer = answer - 273.15;
	answer = answer * 9.0 / 5.0 + 32.0;
	dtostrf(answer,2,2,volts);
	UART_Puts(volts);
	//dtostrf((double)Acc,2,2,volts);
	UART_Puts(volts);
	//volts[0x0] = 48 + (Acc / 0x7FE);
	//Acc = Acc % 0x7FE;
	//volts[0x2] = ((Acc *0xA) / 0x7FE) + 48;
	//Acc = (Acc * 0xA) % 0x7FE;
	//if (Acc >= 0x3FF) volts[0x2]++;
	/*if (volts[0x2] == 58)
	{
		volts[0x2] = 48;
		volts[0x0]++;
	}*/
	//UART_Puts(volts);
	//UART_Puts(MS6);
	//snprintf(output,15,"%f",1.2);//FULL(Acc));
	//dtostrf((double)FULL((double)Acc),2,2,volts);
	//UART_Puts(volts);
	UART_Puts(" degree F");
	/*
		Re-engineer this subroutine to display temperature in degrees Fahrenheit on the Terminal.
		The potentiometer simulates a thermistor, its varying resistance simulates the
		varying resistance of a thermistor as it is heated and cooled. See the thermistor
		equations in the lab 3 folder. User must always be able to return to command line.
	*/
	
}

void EEPROM(void)
{
	UART_Puts("\r\nEEPROM Write and Read.");
	UART_Puts("\r\nEnter a EEPROM Address High");
	for(int i = 0; i < 4; i++) {
		UART_Puts("\r\nEnter the next character in the memory address");
		while (!(ASCII < 16)) {
			ASCII = '\0';
			while (ASCII == '\0')
			{
				UART_Get();
			}
			if (ASCII > 47 && ASCII < 58) {
				ASCII -= 48; //Convert 0-9 to 0-9 (in binary)
			} else if ( ASCII > 64 && ASCII < 71) {
				ASCII -= 55; // Convert A-F to 10-15 (in binary)
			} else {
				UART_Puts("Invalid Character for Address.");
			}
		}
		switch(i) {
			case 0:
				high += ASCII;
				high = high<<4;
			break;
			case 1:
				high += ASCII;
			break;
			case 2:
				low += ASCII;
				low = low<<4;
			break;
			case 3:
				low += ASCII;
			break;
		}
	}				
	UART_Puts("\r\n");
	UART_Puts("(r)ead or (w)rite");
	ASCII = '\0';
	while (ASCII == '\0')
	{
		UART_Get();
	}
	switch(ASCII) {
		case 'w':
			UART_Puts("\r\nPlease provide the character to store at the given location");
			ASCII = '\0';
			while (ASCII == '\0')
			{
				UART_Get();
			}
			EEPROM_Write();
			UART_Puts("\r\n");
			EEPROM_Read();
			//UART_Put();
			//UART_Puts("\r\n");
		break;
		case 'r':
			UART_Puts("\r\n");
			EEPROM_Read();
		break;
		default:
			UART_Puts("Invalid selection. Returning to main menu");
		break;
	}
	
	/*
	Re-engineer this subroutine so that a byte of data can be written to any address in EEPROM
	during run-time via the command line and the same byte of data can be read back and verified after the power to
	the Xplained Mini board has been cycled. Ask the user to enter a valid EEPROM address and an
	8-bit data value. Utilize the following two given Assembly based drivers to communicate with the EEPROM. You
	may modify the EEPROM drivers as needed. User must be able to always return to command line.
	*/

	EEPROM_Write();
	UART_Puts("\r\n");
	EEPROM_Read();
	UART_Put();
	UART_Puts("\r\n");
}


void USART(void)
{
	UART_Puts(MS7);
	UART_Puts(MS11);
	ASCII = '\0';
	while (ASCII == '\0')
	{
		UART_Get();
	}
	switch(ASCII)
	{
		case 'q':
			ASCII = '\0';
			USART_Baud1();
			break;
		case 'w':
			ASCII = '\0';
			USART_Baud2();
			break;
		case 'e':
			ASCII = '\0';
			USART_Baud3();
			break;
		case 'r':
			ASCII = '\0';
			USART_Baud4();
			break;
		case 't':
			ASCII = '\0';
			USART_Baud5();
			break;
		case 'y':
			ASCII = '\0';
			USART_Baud6();
			break;
		case 'u':
			ASCII = '\0';
			USART_Baud7();
			break;
		case 'i':
			ASCII = '\0';
			USART_Baud8();
			break;
		case 'o':
			ASCII = '\0';
			USART_Baud9();
			break;
		case 'p':
			ASCII = '\0';
			USART_Baud10();
			break;
		case 'a':
			ASCII = '\0';
			USART_Baud11();
			break;
		case 's':
			ASCII = '\0';
			USART_Baud12();
			break;
		case 'd':
			ASCII = '\0';
			USART_Baud13();
			break;
		case 'f':
			ASCII = '\0';
			USART_Baud14();
			break;
	}
	ASCII = '\0';
	while (ASCII == '\0')
	{
		UART_Get();
	}
	
	UART_Puts(MS8); // Data Bits
	ASCII = '\0';
	while (ASCII == '\0')
	{
		UART_Get();
	}
	ASCII -= 48;
	ASCII = ASCII<<1;
	USART_Databits();
	ASCII = '\0';
	while (ASCII == '\0')
	{
		UART_Get();
	}
	
	UART_Puts(MS9); //Parity Mode
	ASCII = '\0';
	while (ASCII == '\0')
	{
		UART_Get();		
	}
	ASCII -= 48;
	ASCII = ASCII<<4;
	USART_Parity();
	ASCII = '\0';
	while (ASCII == '\0')
	{
		UART_Get();
	}
	
	UART_Puts(MS10); // Stop Bit
	ASCII = '\0';
	while (ASCII == '\0')
	{
		UART_Get();	
	}
	ASCII -= 49;
	ASCII = ASCII<<3;
	USART_Stopbits();
}


void Command(void)					//command interpreter
{
	UART_Puts(MS3);
	ASCII = '\0';						
	while (ASCII == '\0')
	{
		UART_Get();
	}
	switch (ASCII)
	{
		case 'L' | 'l': LCD();
		break;
		case 'A' | 'a': ADC();
		break;
		case 'E' | 'e': EEPROM();
		break;
		case 'U' | 'u': USART();
		break;
		default:
		UART_Puts(MS5);
		HELP();
		break;  			//Add a 'USART' command and subroutine to allow the user to reconfigure the 						//serial port parameters during runtime. Modify baud rate, # of data bits, parity, 							//# of stop bits.
	}
}



int main(void)
{
	Mega328P_Init();
	Banner();
	while (1)
	{
		Command();				//infinite command loop
	}
}


