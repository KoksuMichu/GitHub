#include "urlmon.h"

void download_html(char* url)
{
	char nazwapliku[80] = "ToParse.html";
	//cout << "Trwa proba pobrania zrodla strony: " << url << endl;
	HRESULT hr = URLDownloadToFile(NULL, url, nazwapliku, 0, NULL);
	/*if (hr == S_OK)
	{
		cout << "Pobranie strony zakonczylo sie powodzeniem.\n";
	}
	else
	{
		cout << "Pobranie strony nie powiodlo sie. Kod bledu: " << hr << "\n";
	}*/
}

typedef struct daysss
{
	char day[20];
	char state[50];
	char temp[5];
	char wind[20];
} days_t;

char lines[9][2048];
bool began = false;
int i = 0;
days_t* dni[10];
int currentday = 0;

void upcase()
{
	for(int j = 0; j < strlen(dni[i].day); j++)
		dni[i].day[j] = toupper(dni[i].day[j]);
	for(int j = 0; j < strlen(dni[i].state); j++)
		dni[i].state[j] = toupper(dni[i].state[j]);
	for(int j = 0; j < strlen(dni[i].day); j++)
		dni[i].temp[j] = toupper(dni[i].temp[j]);
	for(int j = 0; j < strlen(dni[i].day); j++)
		dni[i].wind[j] = toupper(dni[i].wind[j]);
}

/*FILE* file;

void save_file()
{
	file = fopen("details.txt", "w");
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < strlen(dni[i].wind); j++)
		{
			if(dni[i].wind[j] > '0' && dni[i].wind[j] < '9')
			{
				dni[i].wind[j-1] = ';';
				break;
			}
		}
		for(int j = 0; j < strlen(dni[i].day); j++)
			dni[i].day[j] = toupper(dni[i].day[j]);
		for(int j = 0; j < strlen(dni[i].state); j++)
			dni[i].state[j] = toupper(dni[i].state[j]);
		for(int j = 0; j < strlen(dni[i].day); j++)
			dni[i].temp[j] = toupper(dni[i].temp[j]);
		for(int j = 0; j < strlen(dni[i].day); j++)
			dni[i].wind[j] = toupper(dni[i].wind[j]);
		fprintf(file, "%s;%s;%s;%s\n", dni[i].day, dni[i].state, dni[i].temp, dni[i].wind);
	}
	fclose(file);
}*/


void replacer(char* source)
{
	int pos = 0;
	char beg[50];
	char end[50];
	char bufor[50];

	do {
		pos = 0;
		if(strstr(source, "&"))
		{
			while(source[pos] != '&')
				pos++;
		memcpy(beg, &source[0], pos);
		memcpy(end, &source[pos+6], strlen(source)-(pos+6));
		beg[pos] = '\0';
		end[strlen(source)-(pos+6)] = '\0';
		strcpy(bufor, beg);
		if(strstr(source, "&#380"))
			strcat(bufor, "z");
		else
		if(strstr(source, "&#322"))
			strcat(bufor, "l");
		else
		if(strstr(source, "&#347"))
			strcat(bufor, "s");
		strcat(bufor, end);
		strcpy(source, bufor);
		}
	} while(strstr(source, "&"));
}

void exp()
{
	char temp[20];
	char temp2[5];
	for(int i = 0; i < 8; i++)
	{
		strcpy(temp, dni[i].day);
		if(dni[i].day[0] == 'p' && dni[i].day[1] == 'o') strcpy(dni[i].day/*temp*/, "poniedzialek"); else
		if(dni[i].day[0] == 'w' && dni[i].day[1] == 't') strcpy(dni[i].day/*temp*/, "wtorek"); else
		if(dni[i].day[0] == 's' && dni[i].day[1] == 'r') strcpy(dni[i].day/*temp*/, "sroda"); else
		if(dni[i].day[0] == 'c' && dni[i].day[1] == 'z') strcpy(dni[i].day/*temp*/, "czwartek"); else
		if(dni[i].day[0] == 'p' && dni[i].day[1] == 't') strcpy(dni[i].day/*temp*/, "piatek"); else
		if(dni[i].day[0] == 's' && dni[i].day[1] == 'o') strcpy(dni[i].day/*temp*/, "sobota"); else
		if(dni[i].day[0] == 'n' && dni[i].day[1] == 'i') strcpy(dni[i].day/*temp*/, "niedziela");
		memcpy(temp2, &temp[3], 2);
		temp2[2] = '\0';
		strcat(dni[i].day, ", ");
		strcat(dni[i].day, temp2);
	}
}

void obtain_lines()
{
	ifstream fin("toParse.html");
	char szBuff[2048];
	char bufor[50];
	char first = true;
	int pos, pos2;
	// dni miesiaca
	while(fin.getline(szBuff, 2048))
	{
		if(strstr(szBuff, "g3_14_day"))
		{
			began = true;
		}
		if(!first && began && strstr(szBuff, "http://images.weatheronline.pl/gfx/tsub.gif"))
		{
			pos = 0;
			while(szBuff[pos] != '>') {
				pos++;
			}
			pos2 = pos;
			while(szBuff[pos2] != '<') {
				pos2++;
			}
			memcpy(dni[currentday].day, &szBuff[pos + 1], pos2-(pos+1));
			dni[currentday].day[pos2-(pos+1)] = '\0';
			currentday++;
		}
		if(currentday == 8)
			break;
		if(first && began && strstr(szBuff, "http://images.weatheronline.pl/gfx/tsub.gif"))
			first = false;
	}

	currentday = 0;

	// temperatura
	while(fin.getline(szBuff, 2048))
	{
		if(began && (strstr(szBuff, "class=\"t1\"") || strstr(szBuff, "class=\"t2\"") || strstr(szBuff, "class=\"t3\"")))
		{
			pos = 0;
			while(szBuff[pos] != '>') {
				pos++;
			}
			pos2 = pos;
			while(szBuff[pos2] != '<') {
				pos2++;
			}
			memcpy(dni[currentday].temp, &szBuff[pos + 1], pos2-(pos+1));
			dni[currentday].temp[pos2-(pos+1)] = '\0';
			currentday++;
		}
		if(currentday == 8)
			break;
	}

	began = false;
	currentday = 0;

	// stan pogody
	while(fin.getline(szBuff, 2048))
	{
		if(!began && (strstr(szBuff, "przed")))
			began = true;
		if(began && (strstr(szBuff, "class=\"t4\"") || strstr(szBuff, "class=\"t5\"") || strstr(szBuff, "class=\"t6\"")))
		{
			pos = 162;
			while(szBuff[pos] != '"')
				pos++;
			pos2 = pos + 1;
			while(szBuff[pos2] != '\"')
				pos2++;
			memcpy(dni[currentday].state, &szBuff[pos + 1], pos2-(pos+2/*+1*/));
			//dni[currentday].state[pos2-(pos)] = '\0';
			dni[currentday].state[pos2-(pos+2/*+1*/)] = '\0';
			currentday++;
		}
		if(currentday == 8)
			break;
	}

	began = false;
	currentday = 0;

	// wiatr
	while(fin.getline(szBuff, 2048))
	{
		if(began)
		{
			pos = 0;
			while(szBuff[pos] != '>') {
				pos++;
			}
			pos2 = pos;
			while(szBuff[pos2] != '<') {
				pos2++;
			}
			memcpy(dni[currentday].wind, &szBuff[pos + 1], pos2-(pos+1));
			dni[currentday].wind[pos2-(pos+1)] = '\0';
			currentday++;
		}
		if(!began && strstr(szBuff, "Bft"))
			began = true;
		if(currentday == 8)
			break;
	}

	for(int i = 0; i < 8; i++)
	{
		replacer(dni[i].day);
		replacer(dni[i].state);
		replacer(dni[i].temp);
		replacer(dni[i].wind);
	}
}

void out()
{
	for(int i = 0; i < 8; i++)
	{
		cout << "Dzien: " << dni[i].day << endl << "Temperatura ('C): " << dni[i].temp << endl << "Pogoda: " << dni[i].state << endl << "Wiatr: " << dni[i].wind << endl << endl;
	}
}

/*int _tmain(int argc, _TCHAR* argv[])
{
	download_html("http://www.weatheronline.pl/weather/maps/city?PLZ=60-175&PLZN=Pozna%C5%84&LANG=pl&CEL=C&SI=kph&CONT=plpl&LAND=PLP&REGION=0001&WMO=12330&LEVEL=52&R=0&NOREGION=0");
	obtain_lines();
	exp();
	//out();
	save_file();
	out();
	cin.ignore(2);
	return 0;
}
*/
