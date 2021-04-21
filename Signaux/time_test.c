#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <unistd.h>


int main()
{

	char timecoffestr[sizeof "HH:MM"];
	scanf("%s",timecoffestr);
	
	int timecoffe = 0;
	for (int i = 0; i < (int)strlen(timecoffestr); ++i)
	{	
		if(timecoffestr[i] >= '0' && timecoffestr[i] <= '9')
		{
			timecoffe += (int)(timecoffestr[i]-'0');
			timecoffe *= 10;
		}
		else if (timecoffestr[i] != ':' && timecoffestr[i] != '\n')
			errx(EXIT_FAILURE,"please enter a correct time in number \"hour:mins\"");
	}
	timecoffe/=10;

	if(timecoffe > 2359)
			errx(EXIT_FAILURE,"please enter a correct time \"hour:mins\"");

	int temptime = timecoffe;

	for (int i = 0; i < 2; ++i)
	{
			int j = temptime % 100;
			temptime /= 100;
			if(i == 0 && j > 59)
				errx(EXIT_FAILURE,"please enter a correct time");
			if(i == 1 && j > 23)
				errx(EXIT_FAILURE,"please enter a correct time");

	}

	// lire l'heure courante
   	time_t now = time (NULL);

   	// la convertir en heure locale
	struct tm tm_now = *localtime (&now);

	// Creer une chaine HHMM
	char s_now[sizeof"HHMM"];

	strftime (s_now, sizeof s_now, "%H%M", &tm_now);

	int timenow = atoi(s_now);
	// afficher le resultat :
	printf ("'%d'\n", timenow);

	printf("'%d'\n", timecoffe);
	int hours = timecoffe/100;
	int mins = hours *60 + timecoffe%100;

	int nowh = timenow/100;
	int nowm = nowh*60 + timenow%100;

	int m = 0;
	while(mins != nowm)
	{
		//printf("%d\n", m);
		if(mins == 0 && mins != nowm)
			mins = 24*60;
		if(mins != nowm)
		{
			m+=1;
			mins -= 1;
		}
	}
	int secondes = m*60;
	printf("%d\n", secondes);
	sleep(secondes);
	printf("your coffe start now\n");
	return 0;
}
