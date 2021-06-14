#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <err.h>
#include <string.h>
#include <unistd.h>


int main()
{
	printf("Time chosen = ");
	char timecoffeestr[sizeof "HH:MM"];

	scanf("%s",timecoffeestr);
	printf("\n==================\n");

	int timecoffee = 0;
	for (int i = 0; i < (int)strlen(timecoffeestr); ++i)
	{	
		if(timecoffeestr[i] >= '0' && timecoffeestr[i] <= '9')
		{
			timecoffee += (int)(timecoffeestr[i]-'0');
			timecoffee *= 10;
		}
		else if (timecoffeestr[i] != ':' && timecoffeestr[i] != '\n')
			errx(EXIT_FAILURE,"please enter a correct time in number \"hour:mins\"");
	}
	timecoffee/=10;

	if(timecoffee > 2359)
			errx(EXIT_FAILURE,"please enter a correct time \"hour:mins\"");

	int temptime = timecoffee;

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

    // Convertion string -> int
	int timenow = atoi(s_now);

	// afficher le resultat :

	printf("\nActual hour :\t\t");
	printf ("'%d'\n", timenow);

	printf("\nRequested hour :\t");
	printf("'%d'\n\n", timecoffee);

    // Convertion des heures en minutes

	int nowh  = timenow/100;
	int nowm  = nowh*60 + timenow%100;

    int hours = timecoffee/100;
    int mins  = hours *60 + timecoffee%100;

    // Calcule de la différence des heures en secondes
	int m = 0;
	while(mins != nowm)
	{
        // Passage de 00h00 à 24h00 (de 0 mins à 1440 mins)
		if(mins == 0 && mins != nowm)
			mins = 24*60;
		if(mins != nowm)
		{
			m+=1;
			mins -= 1;
		}
	}
    // Passage des minutes en secondes
	int secondes = m*60;

	printf("waiting time in seconds : %d\n", secondes);

    // Met en pause le programme durant "secondes" secondes
	sleep(secondes);
	printf("\n==================\n");
	printf("your coffee start now\n");
	return 0;
}
