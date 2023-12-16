/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <eltongid@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:19:57 by eltongid          #+#    #+#             */
/*   Updated: 2023/12/16 21:20:05 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	create_pipes(int num_pipes, int **pipe_fd)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		if (pipe(pipe_fd[i]) == -1)
			return (return_with_error("Pipe failed."));
		i++;
	}
	return (0);
}

int	get_num_pipes(t_list *commands_list)
{
	int			num_pipes;
	t_command	*command;

	num_pipes = 0;
	while (commands_list != NULL)
	{
		command = commands_list->content;
		if (command->operator != NULL)
		{
			if (is_same_string(command->operator, "|"))
				num_pipes++;
		}
		commands_list = commands_list->next;
	}
	return (num_pipes);
}

static int	close_fds_exit(int num_pipes, int **pipe_fd, pid_t *pids)
{
	int	exit_status;

	close_fds(num_pipes, pipe_fd);
	exit_status = wait_processes(num_pipes, pids);
	return (exit_status);
}

static int	ft_fork(t_list *commands_list, int **pipe_fd,
					int num_pipes, pid_t *pids)
{
	int			i;
	int			exit_status;
	t_command	*command;

	i = -1;
	exit_status = 0;
	while (i++ <= num_pipes && commands_list != NULL)
	{
		command = commands_list->content;
		if (command == NULL)
			break ;
		pids[i] = fork();
		if (pids[i] < 0)
			return (return_with_error("Fork failed"));
		else if (pids[i] == 0)
		{
			set_up_fds(pipe_fd, num_pipes, i);
			child_process(command, pipe_fd[i]);
		}
		else
			exit_status = execute_builtin_parent(command, pipe_fd[i]);
		commands_list = commands_list->next;
	}
	exit_status = close_fds_exit(num_pipes, pipe_fd, pids);
	return (exit_status);
}

int	ft_pipe(t_list *commands_list, int num_pipes)
{
	int		**pipe_fd;
	pid_t	*pids;
	int		exit_code;

	pipe_fd = initialize_pipe_fds(num_pipes);
	if (pipe_fd == NULL)
		return (EXIT_FAILURE);
	pids = (int *) malloc (sizeof(int) * (num_pipes + 1));
	if (pids == NULL)
		return (EXIT_FAILURE);
	create_pipes(num_pipes, pipe_fd);
	exit_code = ft_fork(commands_list, pipe_fd, num_pipes, pids);
	close_fds(num_pipes, pipe_fd);
	free_pipe_fds(pipe_fd, num_pipes);
	free(pids);
	return (exit_code);
}
