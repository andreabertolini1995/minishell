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

int **initialize_pipe_fds(int num_pipes)
{
    int **pipe_fd;
    int i;

    pipe_fd = (int**) malloc (sizeof(int*) * num_pipes);
    if (pipe_fd == NULL)
        return (NULL);
    i = 0;
    while (i < num_pipes)
    {
        pipe_fd[i] = (int*) malloc (sizeof(int) * 2);
        if (pipe_fd[i] == NULL)
            return (NULL);
        i++;
    }
    return (pipe_fd);
}

void create_pipes(int num_pipes, int **pipe_fd)
{
    int i;

    i = 0;
    while (i < num_pipes)
    {
        pipe(pipe_fd[i]);
        i++;
    }
}

int get_num_pipes(t_list *commands_list)
{
    int         num_pipes;
    t_command   *command;

    num_pipes = 0;
    while (commands_list != NULL)
    {
        command = commands_list->content;
        if (command->operator != NULL) // to be changed when introducing redirections
            num_pipes++;
        commands_list = commands_list->next;
    }
    return (num_pipes);
}

void    set_up_fds(t_command *command, int **pipe_fd, int num_pipes, int i)
{
    if (i == 0)
        dup2(pipe_fd[i][1], STDOUT_FILENO);
    else if (i > 0 && i < num_pipes)
    {
        dup2(pipe_fd[i - 1][0], STDIN_FILENO);
        dup2(pipe_fd[i][1], STDOUT_FILENO);
    }
    else if (i == num_pipes)
        dup2(pipe_fd[i - 1][0], STDIN_FILENO);
    close_fds(num_pipes, pipe_fd);
    execute_cmd(command);
    exit(1);
}

int ft_fork(t_list *commands_list, int **pipe_fd, int num_pipes, int *pids)
{
    int         i;
    t_command   *command;

    i = 0;
    while (i < (num_pipes + 1))
    {
        command = commands_list->content;
        pids[i] = fork();
        if (pids[i] < 0 )
            return (1);
        else if (pids[i] == 0)
            set_up_fds(command, pipe_fd, num_pipes, i);
        i++;
        commands_list = commands_list->next;
    }
    return (0);
}

int ft_pipe(t_list *commands_list, int num_pipes)
{
    int **pipe_fd;
    int *pids;

    pipe_fd = initialize_pipe_fds(num_pipes);
    pids = (int*) malloc (sizeof(int) * (num_pipes + 1));
    if (pids == NULL)
        return (1);
    create_pipes(num_pipes, pipe_fd);
    ft_fork(commands_list, pipe_fd, num_pipes, pids);
    close_fds(num_pipes, pipe_fd);
    wait_processes(num_pipes, pids);
    return (0);
}
