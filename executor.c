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

static char	*combine_path_cmd(char *cmd, char *path)
{
	char *path_cmd;
    
    path_cmd = (char*) malloc (sizeof(char) * (ft_strlen(path) + 1 + ft_strlen(cmd)));
    if (path_cmd == NULL)
        return (NULL);
	path_cmd = ft_strncpy(path_cmd, path, ft_strlen(path));
    path_cmd = ft_strcat(path_cmd, "/");
	path_cmd = ft_strcat(path_cmd, cmd);
	return (path_cmd);
}

static char **fill_argv(t_command *command)
{
    char    **argv;
    int     i;

    argv = (char**) malloc (sizeof(char*) * (command->num_args + 2));
    if (argv == NULL)
        return (NULL);
    argv[0] = command->cmd;
    i = 1;
    while (i < (command->num_args + 1))
    {
        argv[i] = command->args[i - 1];
        i++;
    }
    argv[i] = NULL;
    return (argv);
}

static void    execute(t_command *command, char *outfile, char **argv, char *envp[2])
{
    int     file;
    char    *path;
    char    *path_cmd;
    char    **sub_paths;
    int     i;

    if (outfile != NULL)
        file = redirect_output(outfile);
    path = getenv("PATH");
    sub_paths = ft_split(path, ':');
    i = 0;
    while (ft_strncmp(sub_paths[i],  "\0", ft_strlen(sub_paths[i])))
    {
        path_cmd = combine_path_cmd(command->cmd, sub_paths[i]);
        if (execve(path_cmd, argv, envp) == -1)
        {
            i++;
            continue;
            // perror(command->cmd); // error handling to be kept
            // free(argv);
            // exit(1);
        }
    }
}

int execute_cmd(t_command *command, char *outfile)
{
    char    **argv;
	char    *envp[2];
    pid_t   pid;

    argv = fill_argv(command);
    envp[0] = NULL;
    pid = fork();
    if (pid < 0)
    {
        perror("Fork failed");
        free(argv);
        return (1);
    }
    else if (pid == 0)
        execute(command, outfile, argv, envp);
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

static t_list    *update_commands_list(t_list *commands_list, int num_pipes, char *outfile)
{
    int i;

    if (num_pipes == 0)
        commands_list = commands_list->next;
    else
    {
        i = 0;
        while (i < (num_pipes + 1))
        {
            commands_list = commands_list->next;
            i++;
        }
    }
    if (outfile != NULL)
        commands_list = commands_list->next;
    return (commands_list);
}

void    executor(t_list *commands_list)
{
    t_command   *command;
    int         num_pipes;
    char        *outfile;

    /*  Hypothetical scenario where command list is only a chain of pipes
        and a final redirection. */
    num_pipes = get_num_pipes(commands_list);
    outfile = get_name_outfile(commands_list);
    while (commands_list != NULL)
    {
        command = commands_list->content;
        if (num_pipes == 0)
            execute_cmd(command, outfile);
        else
            ft_pipe(commands_list, num_pipes, outfile);
        commands_list = update_commands_list(commands_list, num_pipes, outfile);
    }
}
