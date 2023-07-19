
#include "minishell.h"

int main()
{
    if (access("/bin/ls", F_OK) == 0)
        printf("File exists.\n");
    else
        printf("File does not exist.\n");
}
