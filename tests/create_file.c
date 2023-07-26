#include "fcntl.h"
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>

void execute()
{
    execlp("ls", "ls", "-l", NULL);
}

int main()
{
    int file = open("example.txt", O_WRONLY | O_CREAT, 0777);
    int file2 = dup2(file, STDOUT_FILENO); // points to the same exact file example.txt
    close(file);
    execute();
}