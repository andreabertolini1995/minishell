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

#include "minishell.h"

int execute_cmd(t_command *command)
{
    char    *path_cmd;
    char    **argv;
	char    *envp[2];
    int     i;
    pid_t   pid;
    int     status;
    
    argv = (char**) malloc (sizeof(char*) * (command->num_args + 2));
    if (argv == NULL)
        return (1);
    argv[0] = command->cmd;
    i = 1;
    while (i < (command->num_args + 1))
    {
        argv[i] = command->args[i - 1];
        i++;
    }
    argv[i] = NULL;
    envp[0] = "/bin";
    envp[1] = NULL;
    pid = fork();
    if (pid < 0)
    {
        perror("Fork failed");
        free(argv);
        return (1);
    }
    else if (pid == 0)
    {
        path_cmd = combine_path_cmd(command->cmd);
        if (execve(path_cmd, argv, envp) == -1)
        {
            perror("Could not execve.");
            free(argv);
            exit(1);
        }
    }
    else
    {
        waitpid(pid, &status, 0); // Wait for the child process to finish
        free(argv);
        return (0);
    }
    return (0);
}
