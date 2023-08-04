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

extern int  g_exit_code;

static char	*combine_cmd_path(char *cmd, char *path)
{
	char *cmd_path;
    
    cmd_path = (char*) malloc (sizeof(char) * (ft_strlen(path) + 1 + ft_strlen(cmd)));
    if (cmd_path == NULL)
        return (NULL);
    cmd_path = ft_strjoin(path, "/");
    cmd_path = ft_strjoin(cmd_path, cmd);
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
        if (is_file(cmd_path))
            return (cmd_path);
        else
            i++;
    }
    return (cmd_path);
}

static void    execute_cmd(t_command *command, char **argv, char *envp[2])
{
    char    *path;
    char    *cmd_path;
    char    **sub_paths;

    if (command->outfile != NULL)
        redirect_output(command);
    if (command->infile != NULL)
        redirect_input(command);
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

bool    is_builtin(char *cmd)
{
    if (is_same_string(cmd, "pwd")
        || is_same_string(cmd, "env")
        || is_same_string(cmd, "echo")
        || is_same_string(cmd, "exit")
        || is_same_string(cmd, "cd")
        || is_same_string(cmd, "export")
        || is_same_string(cmd, "unset"))
        return (true);
    else
        return (false);
}

void    execute_builtin_child(t_command *command, int *pipe_fd)
{
    int     signal_to_send;

    if (is_same_string(command->cmd, "echo"))
        ft_echo(command);
    else if (is_same_string(command->cmd, "pwd"))
        ft_pwd();
    else if (is_same_string(command->cmd, "env"))
        ft_env();
    else if (is_same_string(command->cmd, "exit"))
    {
        signal_to_send = SIGINT;
        write(pipe_fd[1], &signal_to_send, sizeof(int));
        close(pipe_fd[1]);
    }
}

void    execute_builtin_parent(t_command *command, int *pipe_fd)
{
    int signal_from_child;

    if (is_same_string(command->cmd, "cd"))
        ft_cd(command);
    else if (is_same_string(command->cmd, "export"))
        ft_export(command);
    else if (is_same_string(command->cmd, "unset"))
        ft_unset(command);
    else if (is_same_string(command->cmd, "exit"))
    {
        close(pipe_fd[1]);
        read(pipe_fd[0], &signal_from_child, sizeof(int));
        if (signal_from_child == SIGINT)
        {
            close(pipe_fd[0]);
            exit(0);
        }
    }
}

void    child_process(t_command *command, int *pipe_fd)
{
    char    **argv;
	char    *envp[2];

    argv = fill_argv(command);
    envp[0] = NULL;
    close(pipe_fd[0]);
    if (is_builtin(command->cmd))
        execute_builtin_child(command, pipe_fd);
    else
        execute_cmd(command, argv, envp);
    close(pipe_fd[1]);
    free(argv);
    exit(1);
}

int execute(t_command *command)
{
    int     pipe_fd[2];
    pid_t   pid;
    int     wstatus;

    if (pipe(pipe_fd) == -1)
        return (return_with_error("Pipe failed."));
    pid = fork();
    if (pid < 0)
        return (return_with_error("Fork failed."));
    else if (pid == 0)
        child_process(command, pipe_fd);
    else
    {
        if (is_builtin(command->cmd))
            execute_builtin_parent(command, pipe_fd);
        waitpid(pid, &wstatus, 0);
        if (WIFEXITED(wstatus))
            g_exit_code = WEXITSTATUS(wstatus);
        close(pipe_fd[0]);
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

static t_list    *update_commands_list(t_list *commands_list, t_command *command, int num_pipes)
{
    int i;

    if (num_pipes > 0)
    {
        i = 0;
        while (i < (num_pipes + 1))
        {
            commands_list = commands_list->next;
            i++;
        }
    }
    if (command->outfile != NULL)
        commands_list = commands_list->next;
    if (command->infile != NULL)
        commands_list = commands_list->next;
    else
        commands_list = commands_list->next;
    return (commands_list);
}

void    executor(t_list *commands_list)
{
    t_command   *command;
    int         num_pipes;

    num_pipes = get_num_pipes(commands_list);
    while (commands_list != NULL)
    {
        command = commands_list->content;            
        if (num_pipes == 0)
            execute(command);
        else
            ft_pipe(commands_list, num_pipes);
        commands_list = update_commands_list(commands_list, command, num_pipes);
    }
}
