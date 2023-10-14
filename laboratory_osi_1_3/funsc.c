#include <stdio.h>
#include "enums.h"

input_code analysis(int argc, char** argv){
    if(argc != 3)
    {
        return isc_bad_input;
    }
    return isc_well;
}

problems_file task(char* input_file_name, char* output_file_name)
{
    FILE *input_file = NULL;
    FILE* output_file = NULL;
    if (!(input_file = fopen(input_file_name, "r"))) {
        return tf_input_trouble;
    }

    if (!(output_file = fopen(output_file_name, "w"))) {
        return tf_output_trouble;

    }


    char one_byte = 0;

    size_t count_read = 0;
    size_t count_write = 0;

    while ((count_read = fread(&one_byte, sizeof(char), sizeof(one_byte), input_file)))
    {
        count_write = fwrite(&one_byte, sizeof(char), count_read, output_file);
        if(count_read != count_write){

            return tf_not_the_same;
        }

    }

    fclose(input_file);
    fclose(output_file);
    return tf_well;
}