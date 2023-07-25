/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:33:54 by abertoli          #+#    #+#             */
/*   Updated: 2022/10/21 18:29:38 by abertoli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

/* Example of implement a pipe as in the pipex project.
    Only handling two processes for the moment. */

int main(int argc, char *argv[])
{
    // pipe_fd[0] is the read end of the pipe
    // pipe_fd[1] is the write end of the pipe
    int pipe_fd[2];
    int pid1;
    int pid2;

    if (pipe(pipe_fd) == -1)
        return (1);
    pid1 = fork();
    if (pid1 < 0 )
        return (2);
    else if (pid1 == 0)
    {
        // Child process 1 (ping)
        dup2(pipe_fd[1], STDOUT_FILENO); // takes pipe_fd[1] and duplicates it in pipe_fd[2]
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execlp("ls", "ls", "-l", NULL);
    }
    pid2 = fork();
    if (pid2 < 0)
        return (3);
    else if (pid2 == 0)
    {
        // Child process 2 (grep)
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        close(pipe_fd[1]);
        execlp("wc", "wc", "-l", NULL);
    }
    close(pipe_fd[0]);
    close(pipe_fd[1]);

    // Wait for child process 1 to finish
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
    return (0);
}



// int ft_pipe(t_command *cmd1, t_command *cmd2, t_command *cmd3)
// {
//     // pipe_fd[0] is the read end of the pipe
//     // pipe_fd[1] is the write end of the pipe
//     int pipe_fd[2][2]; // same as number of pipes
    
//     // Same as number of commands
//     int pid1;
//     int pid2;
//     int pid3;

//     int i;
//     int num_pipes = 2;

//     i = 0;
//     while (i < num_pipes)
//     {
//         if (pipe(pipe_fd[i]) < 0)
//             return (1);
//         i++;
//     }

//     /* First process. */
//     pid1 = fork();
//     if (pid1 < 0 )
//         return (2);
//     else if (pid1 == 0)
//     {
//         // Child process 1
//         close(pipe_fd[0][0]);
//         close(pipe_fd[1][0]);
//         close(pipe_fd[1][1]);
//         dup2(pipe_fd[0][1], STDOUT_FILENO);
//         close(pipe_fd[0][1]);
//         execute_cmd(cmd1);
//         exit(1);
//     }

//     /* Second process. */
//     pid2 = fork();
//     if (pid2 < 0)
//         return (3);
//     else if (pid2 == 0)
//     {
//         // Child process 2
//         close(pipe_fd[0][1]);
//         close(pipe_fd[1][0]);
//         dup2(pipe_fd[0][0], STDIN_FILENO);
//         dup2(pipe_fd[1][1], STDOUT_FILENO);
//         close(pipe_fd[1][1]);
//         close(pipe_fd[0][0]);
//         execute_cmd(cmd2);
//         exit(1);
//     }

//     /* Third process. */
//     pid3 = fork();
//     if (pid3 < 0)
//         return (3);
//     else if (pid3 == 0)
//     {
//         // Child process 3
//         close(pipe_fd[0][1]);
//         close(pipe_fd[0][0]);
//         close(pipe_fd[1][1]);
//         dup2(pipe_fd[1][0], STDIN_FILENO);
//         close(pipe_fd[1][0]);
//         execute_cmd(cmd3);
//         exit(1);
//     }

//     /* Closing the file descriptors. */
//     i = 0;
//     while (i < num_pipes)
//     {
//         close(pipe_fd[i][0]);
//         close(pipe_fd[i][1]);
//         i++;
//     }

//     // Wait for child process 1 to finish
//     waitpid(pid1, NULL, 0);
//     waitpid(pid2, NULL, 0);
//     waitpid(pid3, NULL, 0);
//     return (0);
// }