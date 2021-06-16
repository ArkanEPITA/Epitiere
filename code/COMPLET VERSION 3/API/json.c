#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include <jansson.h>
#include "json.h"


void get_json_file(struct get_json get[10])
{
    json_t *json = json_load_file("../API/test.json", 0, NULL);

    for (size_t pos = 0; pos < 10; pos++)
    {
        json_t *coffee = json_array_get(json, pos);

        json_t *type = json_object_get(coffee, "type");
        json_t *heure = json_object_get(coffee, "heure");
        json_t *activate = json_object_get(coffee, "activate");

        get[pos].type = (char *)json_string_value(type);
        get[pos].heure = (int)json_integer_value(heure);
        get[pos].activate = (int)json_integer_value(activate);
    }
}



void put_json_file(char index, char* value, char* key)
{

    
    json_t *json = json_load_file("../API/test.json", 0, NULL);

    int pos = index - '0';

    if(strcmp(value, "type") == 0)
    {
        json_object_set(json_array_get(json, pos), value, json_string(key));
    }
    else
    {
        json_object_set(json_array_get(json, pos), value, json_integer(atoi(key)));
    }

    

    json_dump_file(json, "../API/test.json", JSON_INDENT(4));
}


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
