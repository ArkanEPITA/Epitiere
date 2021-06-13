#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include <jansson.h>
#include "json.h"


/*struct get_json{
    char* type;
    int heure;
    int activate;
};
*/
//struct get_json get[10];

void get_json_file(struct get_json get[10])
{

    json_t *json = json_load_file("./test.json", 0, NULL);

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



void put_json_file(char *index, char* value, char* key)
{
    json_t *json = json_load_file("./test.json", 0, NULL);
/*
    size_t max = json_array_size(json); //BE CAREFUL TO BE SURE THAT "json" IS AN ARRAY
    size_t pos = 0;

    while(pos < max)
    {
        json_object_set(json_array_get(json, pos), "type", json_string("long"));
        pos += 1;
    }
*/
    int pos = atoi(index);

    if(strcmp(value, "type") == 0)
    {
        json_object_set(json_array_get(json, pos), value, json_string(key));
    }
    else
    {
        json_object_set(json_array_get(json, pos), value, json_integer(atoi(key)));
    }

    

    json_dump_file(json, "./test.json", JSON_INDENT(4));
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

int main(int argc, char* argv[])
{
    struct get_json get[10];

    if(argc < 2)
    {
        errx(EXIT_FAILURE, "Need at least 1 argument");
    }

    printf("%s\n", argv[1]);

    if(strcmp(argv[1], "get") == 0)
    {

        get_json_file(get);

        printf("[\n");
        for (size_t pos = 0; pos < 10; pos++)
        {
            char* type = get[pos].type;
            int heure = get[pos].heure;
            int activate = get[pos].activate;

            printf("{\n\ttype: %s\n\theure: %d\n\tactivate: %d\n}\n", type, heure, activate);
        }
        printf("]\n");
    }
    else if(strcmp(argv[1], "put") == 0)
    {
        if(argc != 5)
        {
            errx(EXIT_FAILURE, "Need 3 other argument with \"put\" : index, value, key");
        }
        else
        {
            put_json_file(argv[2], argv[3], argv[4]);
        }
    }


    return EXIT_SUCCESS;
}