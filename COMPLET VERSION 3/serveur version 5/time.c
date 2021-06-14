#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <unistd.h>
#include "time.h"

int coffee(int Hours, int Mins)
{
	// lire l'heure courante
   	time_t now = time (NULL);

   	// la convertir en heure locale
	struct tm tm_now = *localtime (&now);

	// Creer une chaine HHMM
	char s_now[sizeof"HHMM"];

	strftime (s_now, sizeof s_now, "%H%M", &tm_now);

	int timenow = atoi(s_now);

	int timecoffe = Hours*100 + Mins;

	if(timecoffe > 2359)
			errx(EXIT_FAILURE,"please enter a correct time \"hours:mins\"");

	for (int i = 0; i < 2; ++i)
	{
			int j = timecoffe % 100;
			timecoffe /= 100;
			if(i == 0 && j > 59)
				errx(EXIT_FAILURE,"please enter a correct time");
			if(i == 1 && j > 23)
				errx(EXIT_FAILURE,"please enter a correct time");

	}
	int mins = Hours *60 + Mins;

	int nowh = timenow/100;
	int nowm = nowh*60 + timenow%100;

	int m = 0;
	while(mins != nowm)
	{
		if(mins == 0 && mins != nowm)
			mins = 24*60;
		if(mins != nowm)
		{
			m+=1;
			mins -= 1;
		}
	}
	
	int secondes = m*60;
	//printf("%d\n", secondes);
	//sleep(secondes);

	//insert starting coffe function
	
	//printf("your coffee start now\n");
	return secondes;
}
