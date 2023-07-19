
#include "minishell.h"

int main()
{
    char *tokens[3] = {"Hello", "Bye", "Ola"};
    char token = "Hello";
    printf("Size %lu\n", sizeof(tokens)/sizeof(char*));
}