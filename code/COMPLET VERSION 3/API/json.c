#include <stdlib.h>
#include <stdio.h>
#include <err.h>
#include <string.h>
#include <jansson.h>
#include "json.h"

// get request to a json file
void get_json_file(struct get_json get[10])
{
	// load a json file
    json_t *json = json_load_file("../API/coffee.json", 0, NULL);

    // construction of an array
    for (size_t pos = 0; pos < 10; pos++)
    {
    	// get an array with 3 value at index pos in the json file
        json_t *coffee = json_array_get(json, pos);

        // get every object of an array in different variable
        json_t *type = json_object_get(coffee, "type");
        json_t *heure = json_object_get(coffee, "heure");
        json_t *activate = json_object_get(coffee, "activate");

        // put the value in the array
        get[pos].type = (char *)json_string_value(type);
        get[pos].heure = (int)json_integer_value(heure);
        get[pos].activate = (int)json_integer_value(activate);
    }
}


// change the value of a key at an index
void put_json_file(char index, char* value, char* key)
{

    // load a json file
    json_t *json = json_load_file("../API/coffee.json", 0, NULL);

    int pos = index - '0';


    if(strcmp(value, "type") == 0)
    {
    	// change the value of a type to the new value
        json_object_set(json_array_get(json, pos), value, json_string(key));
    }
    else
    {
    	// change the value of activate or heure by the new value
        json_object_set(json_array_get(json, pos), value, json_integer(atoi(key)));
    }

    
    // put the modification in the file
    json_dump_file(json, "../API/coffee.json", JSON_INDENT(4));
}