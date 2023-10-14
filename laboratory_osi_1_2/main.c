#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "string.h"
#include "enums.h"
#include "structs.h"
#include "funcs.c"




int main() {
    int count_of_users = 0;
    User* list_of_users = (User*) malloc(sizeof(User));
    if(list_of_users == NULL){
        printf("no_mem");
        return 0;
    }

    int requests = 1;

    while(requests){
        print_info_main();
        char* action = action_main();

        if(!(strcmp(action, "signup")))
        {
            count_of_users++;
            char* username = get_login();
            int peerson = find_user(&list_of_users, count_of_users-1, username);
            while(peerson >= 0){
                printf("\nsuch a user already exists, come up with another nickname!\n");
                username = get_login();
                peerson = find_user(&list_of_users, count_of_users-1, username);
            }
            int password = get_password();
            more_mem_for_list_os_users(&list_of_users, count_of_users);
            list_of_users[count_of_users-1].password = password;
            list_of_users[count_of_users-1].login = username;
            list_of_users[count_of_users-1].count_sanctions = 200;
            user_performance(&list_of_users[count_of_users-1], &list_of_users, count_of_users);
            continue;
        }
        else if(!(strcmp(action, "signin")))
        {
            printf("Input your nickname :\n");
            char nickname[10];

            fflush(stdin);
            fgets(nickname, 10, stdin);
            int len_nickname = strlen(nickname);
            while(len_nickname > 7){
                printf("too long nickname, you've made a mistake, repeat, please!\n?-");
                fflush(stdin);
                fgets(nickname, 10, stdin);
                len_nickname = strlen(nickname);
            }
            nickname[len_nickname - 1] = '\0';
            int position_user = find_user(&list_of_users, count_of_users, nickname);
            if(position_user == -1){
                printf("There aren't such user\n\n");
                continue;
            }

            int pass = get_password();
            while(list_of_users[position_user].password != pass){
                printf("the password does not fit, repeat\n");
                pass = get_password();
            }
            user_performance(&list_of_users[position_user], &list_of_users, count_of_users);

            continue;
        }
        else if(!(strcmp(action, "q")))
        {
            requests = 0;
            continue;
        }
        else{
            continue;
        }


    }

    for(int i = 0; i < count_of_users; ++i)
    {
        list_of_users[i].password = -1;
        list_of_users[i].count_sanctions = -1;
        free(list_of_users[i].login);
    }
    free(list_of_users);






}


