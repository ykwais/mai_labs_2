#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>



void search_string(const char *name, const char *string)
{

    FILE *file = fopen(name, "r");
    if (file == NULL)
    {
        printf("Error opening file");
        exit(1);
    }

    char line[100];
    int line_pos = 1;
    bool found = 0;

    while (fgets(line, sizeof(line), file) != NULL)
    {
        if (strstr(line, string) != NULL)
        {
            printf("in file %s string # %d)\n", name, line_pos);
            found = true;
        }
        line_pos++;
    }

    if (!found)
    {
        printf("no string in file: %s\n", name);
    }

    fclose(file);
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("wrong argc\n");
        return 1;
    }

    const char *input_filename = argv[1];
    const char *searchstring = argv[2];

    FILE *files_list = fopen(input_filename, "r");
    if (files_list == NULL)
    {
        printf("problem with file opening\n");
        return 1;
    }

    char filename[100];

    while (fgets(filename, sizeof(filename), files_list) != NULL)
    {

        size_t length = strlen(filename);
        if (length > 0 && filename[length - 1] == '\n')
        {
            filename[length - 1] = '\0';
        }

        search_string(filename, searchstring);

        pid_t childPid = fork(); // создаем новый процесс
        if (childPid == -1)
        {
            printf("Error creating child process");
            return 1;
        }

        if (childPid == 0)
        {

            search_string(filename, searchstring);
            exit(0);
        } else {}
    }

    fclose(files_list);

    int status;
    pid_t wpid;


    while ((wpid = wait(&status)) > 0)
    {
        if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
        {
            printf("well\n");
        }
        else
        {
            printf("problem\n");
        }
    }

    return 0;
}