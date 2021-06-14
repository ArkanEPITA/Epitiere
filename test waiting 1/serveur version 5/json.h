#ifndef JSON
#define JSON


typedef struct get_json{

	// type of the coffe
    char* type;

    // programmed hour of the coffe
    int heure;

    // if 0 the coffe is not activate else its activate
    int activate;
}get_json;

//struct get_json get[10];

// get request to a json file
void get_json_file(struct get_json get[10]);

// change the value of a key at an index
void put_json_file(char *index, char* value, char* key);

// return the next_index
char next_index();

#endif