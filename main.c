#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

//parsed tokens are stored in argv array
char *argv[100];

//parses the entered input command
int parser(char *command) {
    int argc = 0;
    char *token = strtok(command, " ");
    while (token != NULL) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }
    return argc;
}

//resets argv to null every time a new command is entered
void argv_reset(int argc) {
    for (int i = 0; i < argc; i++) {
        argv[i] = NULL;
    }
}

//evaluates the code
int evaluate(int argc) {
    if (!strcmp(argv[0], "exit")) {
        puts("Exiting the code !");
        exit(0);
    }
    if (!strcmp(argv[0], "help")) {
        puts("type 'exit' to exit...");
        return 0;
    }
    pid_t pid = fork();
    if (!pid) {
        execvp(argv[0], argv);
        perror("execvp");
        exit(1);
    } else if (pid < 0) {
        perror("fork");
    } else {
        wait(NULL);
        fflush(stdout);
    }
    return 0;
}

int main() {
    //variable to store command input
    char command_input[256];

    //loops through the cli
    puts("Welcome to ssh cli v1.0.0.");
    puts("Type 'help' for more information.");
    while (1) {
        printf("> ");
        fgets(command_input, 256, stdin);
        command_input[strcspn(command_input, "\n")] = '\0'; // Remove newline
        int argc = parser(command_input);
        evaluate(argc);
        argv_reset(argc);
    }

    return 0;
}