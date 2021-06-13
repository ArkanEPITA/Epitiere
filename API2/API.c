#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include "jansson.h"
#include "json.h"



char next_index()
{
	char res;
	int find = 0;
	int i = 0;
	struct get_json get[10];

	get_json_file(get);

	while(i < 10 && find == 0)
	{
		if(get[i].activate == 0)
		{
			find += 1;
		}
		else 
		{
			i += 1;
		}
	}

	if (find == 0)
	{
		err(3, "no place available");
	}

	res = '0' + i;

	return res;
}

int main()
{
	printf("%c\n", next_index());

	return EXIT_SUCCESS;
}