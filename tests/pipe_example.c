#include "minishell.h"
 #include <sys/wait.h>

int main(int argc, char **argv)
{
    int arr[] = { 1, 2, 3, 4, 1, 2, 7, 7};
    int arrSize = sizeof(arr) / sizeof(int);
    int start, end;
    int fd[2];

    // Setting up the reand and write ends of the pipe
    if (pipe(fd) == -1)
        return 1;

    // Create two processes
    int id = fork();
    if (id == -1)
        return 2;
    
    // Set the start and end point for each process
    if (id == 0)
    {
        start = 0;
        end = arrSize/2;
    }
    else
    {
        start = arrSize / 2;
        end = arrSize;
    }

    // Calculate the sum of the array (common code for each process)
    int sum = 0;
    int i;
    for (i = start; i < end; i++)
        sum += arr[i];
    printf("Calculated partial sum: %d\n", sum);

    // The child process sends the data stored in the "sum" variable
    // to the parent process through the write end of the pipe
    if (id == 0)
    {
        close(fd[0]);
        write(fd[1], &sum, sizeof(sum));
        close(fd[1]);
    }
    // The parent process reads the partial sum sent from the child process
    // and stores it in the sumFromChild variable
    else
    {
        int sumFromChild;
        close(fd[1]);
        read(fd[0], &sumFromChild, sizeof(sumFromChild));
        close(fd[0]);

        int totalSum = sum + sumFromChild;
        printf("Total sum is %d\n", totalSum);
        wait(NULL);
    }

    return 0;
}