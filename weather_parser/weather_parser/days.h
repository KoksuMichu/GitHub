typedef struct dayss
{
char day[20];
char state[50];
char temp[5];
char wind_d[10];
char wind_f[6];
} days;

days DAYS[8];

void assign_days()
{
strcpy(DAYS[0].day, "CZWARTEK, 13");
strcpy(DAYS[0].state, "PRZEWAZNIE SLONECZNIE");
strcpy(DAYS[0].temp, "27");
strcpy(DAYS[0].wind_d, "PLD.");
strcpy(DAYS[0].wind_f, "3-4");
strcpy(DAYS[1].day, "PIATEK, 14");
strcpy(DAYS[1].state, "PRZEWAZNIE SLONECZNIE");
strcpy(DAYS[1].temp, "20");
strcpy(DAYS[1].wind_d, "ZACH.");
strcpy(DAYS[1].wind_f, "3-4");
strcpy(DAYS[2].day, "SOBOTA, 15");
strcpy(DAYS[2].state, "SLONECZNIE");
strcpy(DAYS[2].temp, "25");
strcpy(DAYS[2].wind_d, "PLD.");
strcpy(DAYS[2].wind_f, "3");
strcpy(DAYS[3].day, "NIEDZIELA, 16");
strcpy(DAYS[3].state, "PRZEWAZNIE SLONECZNIE");
strcpy(DAYS[3].temp, "26");
strcpy(DAYS[3].wind_d, "PLD. ZACH.3");
strcpy(DAYS[3].wind_f, "3");
strcpy(DAYS[4].day, "PONIEDZIALEK, 17");
strcpy(DAYS[4].state, "PRZEWAZNIE SLONECZNIE");
strcpy(DAYS[4].temp, "29");
strcpy(DAYS[4].wind_d, "PLD.");
strcpy(DAYS[4].wind_f, "3");
strcpy(DAYS[5].day, "WTOREK, 18");
strcpy(DAYS[5].state, "SLONECZNIE");
strcpy(DAYS[5].temp, "31");
strcpy(DAYS[5].wind_d, "PLD.");
strcpy(DAYS[5].wind_f, "3");
strcpy(DAYS[6].day, "SRODA, 19");
strcpy(DAYS[6].state, "PRZEWAZNIE SLONECZNIE");
strcpy(DAYS[6].temp, "26");
strcpy(DAYS[6].wind_d, "PLN.");
strcpy(DAYS[6].wind_f, "3");
strcpy(DAYS[7].day, "CZWARTEK, 20");
strcpy(DAYS[7].state, "PRZEWAZNIE SLONECZNIE");
strcpy(DAYS[7].temp, "26");
strcpy(DAYS[7].wind_d, "WSCH.");
strcpy(DAYS[7].wind_f, "3");
}