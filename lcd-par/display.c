#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "stm32f4xx_gpio.h"
#include "stm32f4xx.h"
#include "stm32f4xx_spi.h"
#include "display.h"
#include "images.h"
#include "days.h"

int letters[] = {0x7E, 0x11, 0x11, 0x11, 0x7E,// A
0x7F, 0x49, 0x49, 0x49, 0x36,// B
0x3E, 0x41, 0x41, 0x41, 0x22,// C
0x7F, 0x41, 0x41, 0x22, 0x1C,// D
0x7F, 0x49, 0x49, 0x49, 0x41,// E
0x7F, 0x09, 0x09, 0x01, 0x01,// F
0x3E, 0x41, 0x41, 0x51, 0x32,// G
0x7F, 0x08, 0x08, 0x08, 0x7F,// H
0x00, 0x41, 0x7F, 0x41, 0x00,// I
0x20, 0x40, 0x41, 0x3F, 0x01,// J
0x7F, 0x08, 0x14, 0x22, 0x41,// K
0x7F, 0x40, 0x40, 0x40, 0x40,// L
0x7F, 0x02, 0x04, 0x02, 0x7F,// M
0x7F, 0x04, 0x08, 0x10, 0x7F,// N
0x3E, 0x41, 0x41, 0x41, 0x3E,// O
0x7F, 0x09, 0x09, 0x09, 0x06,// P
0x3E, 0x41, 0x51, 0x21, 0x5E,// Q
0x7F, 0x09, 0x19, 0x29, 0x46,// R
0x46, 0x49, 0x49, 0x49, 0x31,// S
0x01, 0x01, 0x7F, 0x01, 0x01,// T
0x3F, 0x40, 0x40, 0x40, 0x3F,// U
0x1F, 0x20, 0x40, 0x20, 0x1F,// V
0x7F, 0x20, 0x18, 0x20, 0x7F,// W
0x63, 0x14, 0x08, 0x14, 0x63,// X
0x03, 0x04, 0x78, 0x04, 0x03,// Y
0x61, 0x51, 0x49, 0x45, 0x43,// Z
0x00, 0x00, 0x00, 0x00, 0x00,// SPACJA
0x3E, 0x51, 0x49, 0x45, 0x3E,// 0
0x00, 0x42, 0x7F, 0x40, 0x00,// 1
0x42, 0x61, 0x51, 0x49, 0x46,// 2
0x21, 0x41, 0x45, 0x4B, 0x31,// 3
0x18, 0x14, 0x12, 0x7F, 0x10,// 4
0x27, 0x45, 0x45, 0x45, 0x39,// 5
0x3C, 0x4A, 0x49, 0x49, 0x30,// 6
0x01, 0x71, 0x09, 0x05, 0x03,// 7
0x36, 0x49, 0x49, 0x49, 0x36,// 8
0x06, 0x49, 0x49, 0x29, 0x1E,// 9
0x00, 0x50, 0x30, 0x00, 0x00,// ,
0x00, 0x36, 0x36, 0x00, 0x00,// :
0x00, 0x05, 0x03, 0x00, 0x00,// '
0x08, 0x08, 0x08, 0x08, 0x08,// -
0x00, 0x30, 0x30, 0x00, 0x00// .
};

void footer()
{
	set_page(7);
	set_0_column();
	write_text(" KOKSU-MICHU PTM 2013 ");
}

void set_66_column()
{
	SetPin_LowE(A0);
	D7_to_D0(SPLC501C_COLUMN_ADDRESS_HI | 4);
	send();
	D7_to_D0(SPLC501C_COLUMN_ADDRESS_LO | 2);
	send();
	SetPin_HighE(A0);
}

//

void put_wuja(int* w)
{
	int i,j;
	//set_page(0);
	for(i=0;i<8;i++)
	{
		set_page(i);
		set_0_column();
		for(j=0;j<110;j++)
		{
			D7_to_D0(w[(110*i)+j]);
			send();
		}
	}
}

//

void put_line(uint8_t page)
{
	set_page(page);
	set_0_column();
	int i;
	D7_to_D0(0x10);
	for (i = 0; i < 132; i++)
	{
		send();
	}
}

/*days DAYS[8];

void assign_days()
{
	strcpy(DAYS[0].day, "SRODA");
	strcpy(DAYS[0].state, "SLONECZNIE");
	strcpy(DAYS[0].temp, "25");
	strcpy(DAYS[0].wind_d, "ZACH.");
	strcpy(DAYS[0].wind_f, "3-4");

	strcpy(DAYS[1].day, "CZWARTEK");
	strcpy(DAYS[1].state, "ZACHMURZENIE ZMIENNE");
	strcpy(DAYS[1].temp, "-3");
	strcpy(DAYS[1].wind_d, "WSCH.");
	strcpy(DAYS[1].wind_f, "2");
}

void load_file(char* filename)
{
	FILE* file = fopen(filename, "r");
	int i;
	for(i = 0; i < 8; i++)
	{
		fscanf(file, "%s;%s;%s;%s;%s\n", DAYS[i].day, DAYS[i].state, DAYS[i].temp, DAYS[i].wind_d, DAYS[i].wind_f);
	}
	fclose(file);
}
*/
//

void show_weather()
{
	int i;
	for(i = 0; i < 8; i++)
	{
		put_line(1);
		put_line(6);
		footer();

		details(DAYS[i].day, DAYS[i].temp, DAYS[i].wind_f, DAYS[i].wind_d, DAYS[i].state, i);

		if(strcmp(DAYS[i].state, "SLONECZNIE"))
			put_image(slo1, slo2);
		else
		if(strcmp(DAYS[i].state, "PRZEWAZNIE SLONECZNIE"))
			put_image(prz_slo1, prz_slo2);
		else
		if(strcmp(DAYS[i].state, "ZMIENNE ZACHMURZENIE"))
			put_image(zach_zm1, zach_zm2);
		else
		if(strcmp(DAYS[i].state, "ZACHMURZENIE PELNE, SLABY DESZCZ"))
			put_image(sd1, sd2);

		ClearScreen();
	}
}

void details(char* day, char* temp, char* wind_force, char* wind_dir, char* state, int ii)
{
	char t[12];
	set_page(0);
	set_0_column();
	write_text(day);
	set_page(2);
	set_0_column();
	strcpy(t, "");
	strcat(t, "TEMP: ");
	strcat(t, temp);
	strcat(t, "'C");
	write_text(t);
	set_page(3);
	set_0_column();
	strcpy(t, "");
	strcat(t, "WIATR: ");
	strcat(t, wind_force);
	write_text(t);
	set_page(4);
	set_0_column();
	write_text(wind_dir);
	set_page(5);
	set_0_column();
	if(strcmp(DAYS[ii].state, "SLONECZNIE"))
			write_text("SLONECZNIE");
	else
	if(strcmp(DAYS[ii].state, "PRZEWAZNIE SLONECZNIE"))
		write_text("MALE CHMURY");
	else
	if(strcmp(DAYS[ii].state, "ZMIENNE ZACHMURZENIE"))
		write_text("POCHMURNO");
	else
	if(strcmp(DAYS[ii].state, "ZACHMURZENIE PELNE, SLABY DESZCZ"))
		write_text("SLABE OPADY");
}

void put_image(int weather1[], int weather2[])
{
	//set_page(SPLC501C_PAGE_ADDRESS | 2);

	int i, j, k;
	//while(1)
	//{
	for(k = 0; k < 3; k++)
	{
		for(i = 0; i < 4; i++)
		{
			set_page(2 + i);
			set_66_column();
			D7_to_D0(0xFF);
			send();
			for(j = 0; j < 64; j++)
			{
				D7_to_D0(weather1[(64*i)+j]);
				send();
			}

		}
		Delayms(200);
		for(i = 0; i < 4; i++)
		{
			set_page(2 + i);
			set_66_column();
			D7_to_D0(0xFF);
			send();
			for(j = 0; j < 64; j++)
			{
				D7_to_D0(weather2[(64*i)+j]);
				send();
			}

		}
		Delayms(200);
	//}
	}
}


void D7_to_D0(uint8_t n)
{
	GPIO_Write(GPIOA, n);
	//Delayms(1);
	/*
	char text[8];
    strcpy (text, "");
    while (n != 0)
    {
    	n % 2 == 0? strcat(text, "0") : strcat(text, "1");
    	n = n / 2;
    }

	text[0] == '1'? SetPin_HighA(D0) : SetPin_LowA(D0);
    text[1] == '1'? SetPin_HighA(D1) : SetPin_LowA(D1);
	text[2] == '1'? SetPin_HighA(D2) : SetPin_LowA(D2);
	text[3] == '1'? SetPin_HighA(D3) : SetPin_LowA(D3);
	text[4] == '1'? SetPin_HighA(D4) : SetPin_LowA(D4);
	text[5] == '1'? SetPin_HighA(D5) : SetPin_LowA(D5);
	text[6] == '1'? SetPin_HighA(D6) : SetPin_LowA(D6);
	text[7] == '1'? SetPin_HighA(D7) : SetPin_LowA(D7);
*/
}

//volatile int f = 0;

void ClearScreen()
{
	uint8_t i = 0;
	while(i < 8) {
		if(i % 4 == 0)
		{
			GPIO_SetBits(GPIOD, GPIO_Pin_12);
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);

		}
		else
		if(i % 4 == 1)
		{
			GPIO_ResetBits(GPIOD, GPIO_Pin_12);
			GPIO_SetBits(GPIOD, GPIO_Pin_13);
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		}
		else
		if(i % 4 == 2)
		{
			GPIO_ResetBits(GPIOD, GPIO_Pin_12);
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
			GPIO_SetBits(GPIOD, GPIO_Pin_14);
			GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		}
		else
		if(i % 4 == 3)
		{
			GPIO_ResetBits(GPIOD, GPIO_Pin_12);
			GPIO_ResetBits(GPIOD, GPIO_Pin_13);
			GPIO_ResetBits(GPIOD, GPIO_Pin_14);
			GPIO_SetBits(GPIOD, GPIO_Pin_15);
		}
		Delayms(1);
		BlankLine(i);
		i++;
	}

}

void BlankLine(uint8_t line)
{
	uint8_t i = 0;

	SetPin_LowE(A0);

	Delayms(1);
	D7_to_D0(SPLC501C_PAGE_ADDRESS | line);
	send();
	D7_to_D0(SPLC501C_COLUMN_ADDRESS_HI);
	send();
	D7_to_D0(SPLC501C_COLUMN_ADDRESS_LO);
	send();
	SetPin_HighE(A0);
	Delayms(1);
	D7_to_D0(0x00);
	for(i=0;i<132;i++)
	{
		send();
	}
}

void send(void)
{
	SetPin_LowE(_CS);
	//Delayms(1);
	SetPin_HighE(_CS);
}

void set_0_column()
{
	SetPin_LowE(A0);
	D7_to_D0(SPLC501C_COLUMN_ADDRESS_HI);
	send();
	D7_to_D0(SPLC501C_COLUMN_ADDRESS_LO);
	send();
	SetPin_HighE(A0);
}

void set_begin()
{
	SetPin_LowE(A0);
	D7_to_D0(SPLC501C_PAGE_ADDRESS);
	send();
	D7_to_D0(SPLC501C_COLUMN_ADDRESS_HI);
	send();
	D7_to_D0(SPLC501C_COLUMN_ADDRESS_LO);
	send();
	SetPin_HighE(A0);
}

void write_text(char* text)
{
	int i;
	for(i = 0; i < strlen(text); i++)
	{
		letter(text[i]);
	}
}


void put(int val)
{
	int i;
	for(i = val; i < val + 5; i++)
	{
		D7_to_D0(letters[i]);
		send();
	}
	D7_to_D0(0x00);
	send();
}

void letter(char l)
{
	//int i;
	switch (l)
	{
	case 'A':
		put(0);
		break;
	case 'B':
		put(5);
		break;
	case 'C':
		put(10);
		break;
	case 'D':
		put(15);
		break;
	case 'E':
		put(20);
		break;
	case 'F':
		put(25);
		break;
	case 'G':
		put(30);
		break;
	case 'H':
		put(35);
		break;
	case 'I':
		put(40);
		break;
	case 'J':
		put(45);
		break;
	case 'K':
		put(50);
		break;
	case 'L':
		put(55);
		break;
	case 'M':
		put(60);
		break;
	case 'N':
		put(65);
		break;
	case 'O':
		put(70);
		break;
	case 'P':
		put(75);
		break;
	case 'Q':
		put(80);
		break;
	case 'R':
		put(85);
		break;
	case 'S':
		put(90);
		break;
	case 'T':
		put(95);
		break;
	case 'U':
		put(100);
		break;
	case 'V':
		put(105);
		break;
	case 'W':
		put(110);
		break;
	case 'X':
		put(115);
		break;
	case 'Y':
		put(120);
		break;
	case 'Z':
		put(125);
		break;
	case ' ':
		put(130);
		break;
	case '0':
		put(135);
		break;
	case '1':
		put(140);
		break;
	case '2':
		put(145);
		break;
	case '3':
		put(150);
		break;
	case '4':
		put(155);
		break;
	case '5':
		put(160);
		break;
	case '6':
		put(165);
		break;
	case '7':
		put(170);
		break;
	case '8':
		put(175);
		break;
	case '9':
		put(180);
		break;
	case ',':
		put(185);
		break;
	case ':':
		put(190);
		break;
	case '\'':
		put(195);
		break;
	case '-':
		put(200);
		break;
	case '.':
		put(205);
		break;
	}
}

void set_page(uint8_t p)
{
	SetPin_LowE(A0);

	D7_to_D0(SPLC501C_PAGE_ADDRESS | p);
	send();

	SetPin_HighE(A0);
}

void display_init(void)
{
	// Reset wyœwietlacza
	SetPin_LowE(_RES);
	Delayms(50);
	SetPin_HighE(_RES);

	SetPin_LowE(A0);
	SetPin_HighE(_RD);
	SetPin_LowE(_WR);

	// POWER SAVER SHOULD BE HERE
	//D7_to_D0(SPLC501C_DISPLAY_REVERSE);
	//send();
	//D7_to_D0(SPLC501C_RESET);
	//send();
	//D7_to_D0(SPLC501C_START_LINE | 0); //0
	//send();
	D7_to_D0(SPLC501C_BIAS_19);
	send();
	D7_to_D0(SPLC501C_ADC_NORMAL);
	send();
	D7_to_D0(SPLC501C_COM63);
	send();
	D7_to_D0(SPLC501C_VOLUME_MODE);
	send();
	D7_to_D0(0x14);//"00010100");
	send();
	D7_to_D0(SPLC501C_DISPLAY_ON);
	send();
	D7_to_D0(SPLC501C_DISPLAY_NORMAL);
	send();
	D7_to_D0(SPLC501C_POWERON);
	send();

	/*
	D7_to_D0(SPLC501C_COLUMN_ADDRESS_LO); //0
	send();
	D7_to_D0(SPLC501C_COLUMN_ADDRESS_HI); //0
	send();
	D7_to_D0(SPLC501C_START_LINE | 0); //0
	send();
	D7_to_D0(SPLC501C_PAGE_ADDRESS | 0); //0
	send();
*/
}

void Delayms(uint32_t ms)
{
// testowane, dla argumentu 1000 trwa blisko sekundê
	volatile int n;
	while(ms)
	{
		n = 16777;
		while(n) n--;
		ms--;
	}
}
