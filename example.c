#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

// void init_shell()
// {
//     printf("\n\n\n\n******************"
//         "************************");
//     printf("\n\n\n\t****MY SHELL****");
//     printf("\n\n\t-USE AT YOUR OWN RISK-");
//     printf("\n\n\n\n*******************"
//         "***********************");
//     char* username = getenv("USER");
//     printf("\n\n\nUSER is: @%s", username);
//     printf("\n");
//     sleep(1);
// }

// int main()
// {
  
//     init_shell();
//     return 0;
// }

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<readline/readline.h>
#include<readline/history.h>

void clear()
{
    // Clearing the shell using escape sequences
    printf("\033[H\033[J");
}
  
// Greeting shell during startup
void init_shell()
{
    printf("\n\n\n\n******************"
        "************************");
    printf("\n\n\n\t****MY SHELL****");
    printf("\n\n\t-USE AT YOUR OWN RISK-");
    printf("\n\n\n\n*******************"
        "***********************");
    char* username = getenv("USER");
    printf("\n\n\nUSER is: @%s", username);
    printf("\n");
    sleep(1);
    clear();
}
  
int takeInput(char* str)
{
    char* buf;
  
    buf = readline(">>> ");
    if (strlen(buf) != 0) {
        add_history(buf);
        return 0;
    } else {
        return 1;
    }
}

int main()
{
    char *inputString;
    init_shell();

    while (42) {
        // Reading input continously from the shell
        if (takeInput(inputString))
            continue;
    }
}

