#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
// <sys/wait.h>

void search_string_in_file(char* filename, char* search_string) {
    int yes = 0;

    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf( "Не удалось открыть файл %s\n", filename);
        return;
    }

    char line[100];
    int line_number = 1;
    while (fgets(line, 100, file) != NULL) {

        if (!strcmp(line, search_string)) {
            printf("Строка найдена в файле %s, строка #%d", filename, line_number);
            yes = 1;
        }
        line_number++;
    }
    if(!yes){
        printf("Строка не найдена в файле %s\n", filename);
    }


    fclose(file);
}

int main(int argc, char** argv) {
    if (argc < 3) {
        printf("мало аргументов!\n");
        return 0;
    }

    char* filenames_file = argv[1];
    char* search_string = argv[2];

    FILE* file = fopen(filenames_file, "r");
    if (file == NULL) {
        printf("Не удалось открыть файл %s\n", filenames_file);
        return 1;
    }

    char filename[100];
    while (fgets(filename, 100, file) != NULL) {

        int length = strlen(filename);
        if(filename[length-1] == '\n' && length > 0){
            filename[length-1] = '\0';
        }

        pid_t pid = fork();
        if(pid == -1){
            printf("проблема с созданием нового процесса\n");
            return 0;
        }
        else if (pid == 0) {

            search_string_in_file(filename, search_string);
            exit(0);

        } else {}

    }

    fclose(file);

//    int status;
//    pid_t child_pid;
//    while ((child_pid = wait(&status)) > 0) {
//        // Обработка статуса завершения процесса-потомка
//        if (WIFEXITED(status)) {
//            int exit_status = WEXITSTATUS(status);
//            if (exit_status != 0) {
//                fprintf(stderr, "Процесс-потомок %d завершился с ошибкой\n", child_pid);
//            }
//        } else {
//            fprintf(stderr, "Процесс-потомок %d завершился некорректно\n", child_pid);
//        }
//    }
}
