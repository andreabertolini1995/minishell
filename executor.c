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

static char	*combine_path_cmd(char *cmd)
{
	char *path;
	char *path_cmd;

	path = "/bin/";
	path_cmd = (char*) malloc (sizeof(char) * (ft_strlen(path) + ft_strlen(cmd)));
	if (path_cmd == NULL)
		return (NULL);
	path_cmd = ft_strncpy(path_cmd, path, ft_strlen(path));
	path_cmd = ft_strcat(path_cmd, cmd);
	return (path_cmd);
}

int execute_cmd(t_command *command)
{
    char    *path_cmd;
    char    **argv;
	char    *envp[2];
    int     i;
    pid_t   pid;
    
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
            perror(command->cmd);
            free(argv);
            exit(1);
        }
    }
    else
    {
        waitpid(pid, NULL, 0);
        free(argv);
        return (0);
    }
    return (0);
}

void close_fds(int num_pipes, int **pipe_fd)
{
    int i;

    i = 0;
    while (i < num_pipes)
    {
        close(pipe_fd[i][0]);
        close(pipe_fd[i][1]);
        i++;
    }
}

void wait_processes(int num_pipes, int *pids)
{
    int i;

    i = 0;
    while (i < (num_pipes + 1))
    {
        waitpid(pids[i], NULL, 0);
        i++;
    }
}

void    executor(t_list *commands_list)
{
    t_command   *command;
    int         num_pipes;
    int         i;

    /* Hypothetical scenario where command list is only a chain of pipes. */
    num_pipes = get_num_pipes(commands_list);
    while (commands_list != NULL)
    {
        command = commands_list->content;
        if (num_pipes == 0)
        {
            execute_cmd(command);
            commands_list = commands_list->next;
        }
        else
        {
            ft_pipe(commands_list, num_pipes);
            i = 0;
            while (i < (num_pipes + 1))
            {
                commands_list = commands_list->next;
                i++;
            }
        } 
    }
}
