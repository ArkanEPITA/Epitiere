#include "jansson.h"
#include <stdlib.h>
#include <stdio.h>
#include <err.h>


json_t *get_json_file()
{
    json_error_t err;

                    //Load the file JSON
    json_t *root = json_load_file("./test.json", 0, &err);

    //Test: is content okay ?
    if(!root)
    {
        json_decref(root);
        errx(EXIT_FAILURE, "Error while loading json file");
    }

    return root;


    //ALL OF THE BELOW IS FOR TESTS ONLY

    //Test: What type is "root" ?
    if(json_is_object(root))
    {
        printf("root is an object\n");
    }

    //If not what's below, print type of root.
    
    else
    {
        printf("root type : %d\n", json_typeof(root));
    }

                    //Get the data inside the "json_object"
    json_t *data = json_object_get(root, "id");

    //Test: Is data an integer ?
    if(json_is_integer(data))
    {
                    //Transform json_int which is not understandable
                    //In C byget_json_data a real int
        int value = json_integer_value(data);
        printf("Coffee id is : %d\n", value);
    }
    //If not of the above, print type of data
    else
    {
        printf("data type is : %d\n", json_typeof(data));
    }

}


int main()
{
    json_t *file = get_json_file();

    json_t *test = json_string("court");

    if(!file)
    {
        printf("File is not okay >:((\n");
    }

    json_t *data = json_object_get(file, "cafe");



    if(json_object_set(data, "cafe", test))
    {
        printf("cafe modified\n");
    }
    else
    {
        printf("cafe not modified\n");
    }

    if(json_dump_file(file, "./test.json", JSON_INDENT(4)))
    {
        printf("JSON file modified\n");
    }
    else
    {
        printf("JSON file not modified\n");
    }

    return EXIT_SUCCESS;
}