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

static char	*combine_cmd_path(char *cmd, char *path)
{
	char *cmd_path;
    
    cmd_path = (char*) malloc (sizeof(char) * (ft_strlen(path) + 1 + ft_strlen(cmd)));
    if (cmd_path == NULL)
        return (NULL);
    cmd_path = ft_strncpy(cmd_path, path, ft_strlen(path));
    cmd_path = ft_strcat(cmd_path, "/");
	cmd_path = ft_strcat(cmd_path, cmd);
	return (cmd_path);
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

char    *get_cmd_path(t_command *command, char **sub_paths)
{
    int     i;
    char    *cmd_path;

    i = 0;
    while (sub_paths[i] != NULL)
    {
        cmd_path = combine_cmd_path(command->cmd, sub_paths[i]);
        if (is_cmd(cmd_path))
            return (cmd_path);
        else
            i++;
    }
    return (cmd_path);
}

static void    execute(t_command *command, char *outfile, char **argv, char *envp[2])
{
    int     file;
    char    *path;
    char    *cmd_path;
    char    **sub_paths;

    if (outfile != NULL)
        file = redirect_output(outfile);
    path = getenv("PATH");
    sub_paths = ft_split(path, ':');
    cmd_path = get_cmd_path(command, sub_paths);
    if (execve(cmd_path, argv, envp) < 0)
    {
        perror(command->cmd);
        free(argv);
        exit(1);
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
