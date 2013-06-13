#define DISP_WIDTH 132
#define DISP_HEIGHT 64
#define DISP_PAGES 8

//#define DISP_DEFAULT_BRIGHTNESS  20

/*
#define CS_Pin					GPIO_Pin_9
#define RST_Pin					GPIO_Pin_10
#define A0_Pin    				GPIO_Pin_11
#define SCLK_Pin   				GPIO_Pin_13
#define SID_Pin   	 			GPIO_Pin_15
#define SCLK_PinSource  		GPIO_PinSource13
#define SID_PinSource 	 		GPIO_PinSource15
*/

// parallel

//PA

#define D7	GPIO_Pin_7
#define D6	GPIO_Pin_6
#define D5	GPIO_Pin_5
#define D4	GPIO_Pin_4
#define D3	GPIO_Pin_3
#define D2	GPIO_Pin_2
#define D1	GPIO_Pin_1
#define D0	GPIO_Pin_0

// PE

#define _RD		GPIO_Pin_0
#define _WR 	GPIO_Pin_1
#define A0		GPIO_Pin_2
#define _RES	GPIO_Pin_3
#define _CS		GPIO_Pin_4

/*
12 - /RD - PE0
13 - /WR - PE1
14 - A0 - PE2
15 - /RES - PE3
16 - /CS1 - PE4
*/

#define SPLC501C_DISPLAY_ON 		0xAF
#define SPLC501C_DISPLAY_OFF		0xAE

#define SPLC501C_START_LINE			0x40

#define SPLC501C_PAGE_ADDRESS		0xB0

#define PAGE_0						0xB0
#define PAGE_1						0xB1
#define PAGE_2						0xB2
#define PAGE_3						0xB3
#define PAGE_4						0xB4
#define PAGE_5						0xB5
#define PAGE_6						0xB6
#define PAGE_7						0xB7

#define SPLC501C_COLUMN_ADDRESS_HI	0x10
#define SPLC501C_COLUMN_ADDRESS_LO	0x00

#define SPLC501C_ADC_NORMAL			0xA0
#define SPLC501C_ADC_REVERSE		0xA1

#define SPLC501C_DISPLAY_NORMAL		0xA6
#define SPLC501C_DISPLAY_REVERSE	0xA7

#define SPLC501C_DISPLAY_ALL_ON		0xA5
#define SPLC501C_DISPLAY_ALL_OFF	0xA4

#define SPLC501C_BIAS_19			0xA2
#define SPLC501C_BIAS_15			0xA3

#define SPLC501C_RMW_START			0xE0
#define SPLC501C_RMW_END			0xEE

#define SPLC501C_RESET				0xE2

#define SPLC501C_COM0				0xC0
#define SPLC501C_COM63				0xC8

#define SPLC501C_POWERON			0x2F

#define SPLC501C_VOLTAGE_RATIO		0x20

#define SPLC501C_VOLUME_MODE		0x81
#define SPLC501C_VOLUME_SET			0x00

#define SPLC501C_PAGE_BLINKING_MODE	0xD5
#define SPLC501C_PAGE_BLINKING_0	0x01
#define SPLC501C_PAGE_BLINKING_1	0x02
#define SPLC501C_PAGE_BLINKING_2	0x04
#define SPLC501C_PAGE_BLINKING_3	0x08
#define SPLC501C_PAGE_BLINKING_4	0x10
#define SPLC501C_PAGE_BLINKING_5	0x20
#define SPLC501C_PAGE_BLINKING_6	0x40
#define SPLC501C_PAGE_BLINKING_7	0x80


#define SetPin_LowA(PIN)		GPIO_ResetBits(GPIOA, PIN)
#define SetPin_HighA(PIN)		GPIO_SetBits(GPIOA, PIN)
#define SetPin_LowE(PIN)		GPIO_ResetBits(GPIOE, PIN)
#define SetPin_HighE(PIN)		GPIO_SetBits(GPIOE, PIN)

/*
#define SPLC501C_PAGE_BLINKING_MODE	0xD5
#define SPLC501C_PAGE_BLINKING_0	0x01
#define SPLC501C_PAGE_BLINKING_1	0x02
#define SPLC501C_PAGE_BLINKING_2	0x04
#define SPLC501C_PAGE_BLINKING_3	0x08
#define SPLC501C_PAGE_BLINKING_4	0x10
#define SPLC501C_PAGE_BLINKING_5	0x20
#define SPLC501C_PAGE_BLINKING_6	0x40
#define SPLC501C_PAGE_BLINKING_7	0x80
*/

/* Inicjalizacja wyœwietlacza */
void display_init(void);
/* Przes³anie jednej komendy (u¿yj makra do wyboru komendy) */
void display_command(uint8_t cmd);
/* Przes³anie bajta danych (zapis w aktualnym po³o¿eniu wewnêtrznego wskaŸnika
   na pamiêæ RAM wyœwietlacza) */
void display_sendData(uint8_t data);
/* Wartoœæ jasnoœci podœwietlenia: z zakresu <0,63> */
void display_setBrightness(uint8_t value);
/* Odwróæ kolory */
void display_invertColors(void);
/* Wyczyszczenie ekranu (w³aœciwie bufora), tj. zgaszenie wszystkich pikseli */
void display_clear(void);
/* Zapalenie wszystkich pikseli (w³aœciwie: ustawienie jedynek w buforze). */
void display_fill(void);
/* Odœwie¿enie wyœwietlanych danych - wywo³aæ po skoñczeniu rysowania. */
void display_refresh(void);
/* Pozosta³e funkcje */
void Delayms(uint32_t ms);
void send();
void D7_to_D0(uint8_t n);
void sendline();
//void toBin();
void ClearScreen();
void BlankLine(uint8_t line);
void set_begin();
void letter(char l);
void set_page(uint8_t p);
void set_0_column();
void write_text(char* text);
void put_image(int* weather1, int* weather2);
void set_66_column();
void put_line(uint8_t page);
void footer();
//
void put_wuja();
void details(char* day, char* temp, char* wind_force, char* wind_dir, char* state, int ii);
//void load_file(char* filename);
void show_weather();

void assign_days();
/*

void assign_days();

typedef struct dayss
{
	char day[20];
	char state[50];
	char temp[5];
	char wind_d[10];
	char wind_f[6];
} days;
*/
