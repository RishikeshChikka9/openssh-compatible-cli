#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//parsed tokens are stored in argv array
char argv[100][100];

//parses the entered input command
int parser(char *command, int argc){
    char flag = 0;
    int i = 0;
    while(*command){
        if(*command == ' '){
            flag++; argc++; command++;
            i = 0;
            continue;
        }
        argv[flag][i] = *command;
        command++; i++;
    }
    return argc;
}

//resets argv to null every time a new command is entered
void argv_reset(int argc){
    for(int i = 0; i < argc; i++)
        for(int j = 0; j < sizeof(argv[i]); j++)
            argv[i][j] = '\0';
}

//evaluates the code
int evaluate(int argc){
    if(!(strcmp(argv[0], "exit\n"))){
        puts("Exiting the code !");
        exit(0);
    }
    return 0;
}

int main(){
    //variable to store command input
    char command_input[300];

    //loops through the cli
    puts("Welcome to ssh cli v1.0.0.");
    puts("Type 'help' for more information.");
    while(1){
        printf("> ");
        fgets(command_input, 300, stdin);
        int argc = parser(command_input, 0);
        evaluate(argc);
        argv_reset(argc);
    }

    return 0;
}