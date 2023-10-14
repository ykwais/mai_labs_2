#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include "enums.h"
#include "structs.h"

#define MAX_LENGTH_LOGIN 6
#define MIN_PASSWORD 0
#define MAX_PASSWORD 100000

void print_info_main(){
    printf("If you lead 'signup', then you will start the registration process.\n If you enter 'signin', you will be able to log in to your username.\n If you enter 'q', the process will end.\n");
}

void print_subinfo(){
    printf("If you enter 'Date', you will find out the current date.\n If you enter 'Time', you will find out the current time.\n If you 'Howmuch <date> flag ', you will find out how much time has passed since that date in seconds (-s), minutes (-m), hours (-h), years(-y).\n If you enter 'Logout', you will return to the main menu. If you 'Sanctions 'username' <number>', then impose restrictions on the user.\n");
}


void more_mem_for_list_os_users(User** list_users, int count_users){
    User* tmp = NULL;
    if(!(tmp = realloc(*list_users, sizeof(User)*count_users)))
    {
        free(*list_users);
        //enum
        return;
    }
    else{
        *list_users = tmp;
    }

}

char* action_main(){
    printf("Enter action:\n");
    printf("?-  ");
    char symb[10];


    char* action = (char*)malloc(sizeof(char) * MAX_LENGTH_LOGIN+1);
    if(action == NULL){
        printf("no mem\n");
        return NULL;//enum
    }

    //scanf("%s", &symb);
    fflush(stdin);
    fgets(symb, 10, stdin);
    int len_name = strlen(symb);
    while(len_name>7){
        printf("too long action, repeat, please!\n?-");
        fflush(stdin);
        //scanf("%s", &symb);
        fgets(symb, 10, stdin);
        len_name = strlen(symb);
    }


    for(int i = 0; i < len_name-1; ++i)
    {
        action[i] = symb[i];
    }
    action[len_name-1] = '\0';


    return action;
}

bool isalnum_string(char* string){
    int length = strlen(string);
    for(int i = 0; i < length; ++i){
        if(!isalnum(string[i])){
            return false;
        }
    }
    return true;
}

char* get_login(){
    printf("log in, please :\n");
    printf("?-  ");
    char symb[10];


    char* username = (char*)malloc(sizeof(char) * MAX_LENGTH_LOGIN+1);
    if(username == NULL){
        printf("no mem\n");
        return NULL;//enum
    }


    fgets(symb, 10, stdin);

    int len_name = strlen(symb);
    if(symb[len_name-1] == '\n'){
        symb[len_name-1] = '\0';
    }
    while(len_name>7 || !isalnum_string(symb)){
        printf("too long nickname or or there are characters other than Latin or numbers, repeat, please!\n?-");

        fflush(stdin);
        fgets(symb, 10, stdin);
        len_name = strlen(symb);
        if(symb[len_name-1] == '\n'){
            symb[len_name-1] = '\0';
        }
    }


    for(int i = 0; i < len_name-1; ++i)
    {
        username[i] = symb[i];
    }
    username[len_name-1] = '\0';


    return username;
}

int get_password(){
    int password = -1;
    char symb[1000];

    char* endptr;
    printf("Input your password:\n?- ");
    scanf("%s", &symb);


    password = strtol(symb, &endptr,10);

    while((password > MAX_PASSWORD || password < MIN_PASSWORD ) || *endptr != '\0')
    {
        printf("You've inputted wrong password or invalid parametr! Repeat please\n");
        printf("Input your password:\n?- ");

        scanf("%s", &symb);
        password = strtol(symb, &endptr,10);
    }

    return password;
}

int find_user(User** list_users, int count_users, char* u_name){
    for(int i = 0; i < count_users; ++i)
    {

        if(!(strcmp((*list_users)[i].login, u_name))){
            return i;
        }
    }
    return -1;//enum

}


void current_time(char *string_of_time) {
    time_t current;
    struct tm* time_info;
    time(&current);
    time_info = localtime(&current);
    strftime(string_of_time, 9, "%H:%M:%S", time_info);
}

void get_current_time(){
    char time[9];
    current_time(time);
    printf("Current time : %s\n\n", time);
}

void current_data(char *string_of_data) {
    time_t current;
    struct tm* data_info;
    time(&current);
    data_info = localtime(&current);
    strftime(string_of_data, 11, "%d.%m.%Y", data_info);
}

void get_current_data(){
    char time[11];
    current_data(time);
    printf("Current data : %s\n\n", time);
}

void how_much(char* string_data, char* flag) {
    if(flag == NULL){
        printf("Invalid flag\n\n");
        return;
    }
    time_t current;
    struct tm* time_info_input;
    time_t input_time;
    long double pass_time;

    time(&current);

    time_info_input = localtime(&current);

    int check_day = -1;
    int check_mon = -1;
    int check_year = -1;



    sscanf(string_data, "%d.%d.%d", &check_day, &check_mon, &check_year);
    if(check_day > 31 || check_day < 1 || check_mon > 12 || check_mon < 1 || check_year > 2023 || check_year < 1900){
        printf("Wrong data was inputted!\n");
        return;
    }
    if(check_year>=1900 && check_year < 1970){
        pass_time = (1970 - check_year-2)*365.25*24*3600 + check_mon*29.3*24*3600 + check_day*24*3600 + (long double)current;
    }else{
        time_info_input->tm_mday = check_day;
        time_info_input->tm_mon = check_mon - 1;
        time_info_input->tm_year = check_year - 1900;

        input_time = mktime(time_info_input);
        if(input_time == -1 ){
            printf("Wrong data was inputted!\n\n");
            return;
        }

        pass_time = difftime(current,input_time);
        if(pass_time == 0.0L){
            printf("It's today!\n\n");
            return;
        }
    }


    if (!(strcmp(flag, "-s\n"))) {
        printf("%.100LF\n\n", pass_time);
    } else if (!(strcmp(flag, "-m\n"))) {
        printf("%.10LF\n\n", pass_time / 60);
    } else if (!(strcmp(flag, "-h\n"))) {
        printf("%.10LF\n\n", pass_time / (60*60));
    } else if (!(strcmp(flag, "-y\n"))) {
        printf("%.1LF\n\n", pass_time / (60*60 * 24 * 365.25));
    } else {
        printf("Invalid flag\n\n");
    }
}

void user_performance(User* user, User** list_users,int count_users){

    while(user->count_sanctions-- > 0){
        printf("The count of sancs are : %d\n\n", user->count_sanctions);
        print_subinfo();
        char input_string[100];
        fflush(stdin);
        printf("Input action: \n?-");
        fgets(input_string, 100, stdin);
        char* istr;
        istr = strtok(input_string, " ");
        while(istr != NULL){

            if(!(strcmp(istr, "Time\n"))){
                get_current_time();
                break;
            }
            else if(!(strcmp(istr, "Date\n"))){
                get_current_data();
                break;
            }
            else if(!(strcmp(istr, "Howmuch"))){
                istr = strtok(NULL, " ");
                //int
                char* date = istr;
                int len_string = strlen(date);
                if(date[len_string-1] == '\n'){
                    date[len_string-1] = '\0';
                }
                istr = strtok(NULL, " ");
                char* flag = istr;
                how_much(date, flag);
                break;
            }
            else if(!(strcmp(istr, "Logout\n"))){
                return;

            }
            else if(!(strcmp(istr, "Sanctions"))){
                char* endptr;
                istr = strtok(NULL, " ");
                char* username = istr;
                int len_string = strlen(username);
                if(username[len_string-1] == '\n'){
                    username[len_string-1] = '\0';
                }
                istr = strtok(NULL, " ");
                char* new_count_sanctions_string = istr;
                int new_count_sanctions = strtol(new_count_sanctions_string, &endptr, 10);
                if(new_count_sanctions<=0 || *endptr != '\n' || !(strcmp(username, user->login))){
                    printf("You will not be able to perform this operation. The new number must be positive! and enter only numbers! Also, you cannot assign a new number of requests to yourself.\n");
                    break;
                }
                int position = find_user(list_users, count_users, username);
                if(position == -1){
                    printf("There aren't such user\n\n");
                    break;
                }
                printf("Input the SPECIAL password for this action:\n-?");
                int special_password = -1;
                scanf("%d", &special_password);
                if(special_password == 12345){
                    (*list_users)[position].count_sanctions = new_count_sanctions;
                    printf("success!\n");
                }
                else{
                    printf("Invalid password!\n");
                }

                break;


            }
            else{
                printf("no such command\n");
                istr = strtok(NULL, " ");
            }


        }

    }
    printf("You have reached the limit of the number of requests! a logout occurred\n\n");
}







