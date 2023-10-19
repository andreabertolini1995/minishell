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

static int	ft_fork(t_list *commands_list, int **pipe_fd,
					int num_pipes, int *pids)
{
	int			i;
	t_command	*command;

	i = 0;
	while (i < (num_pipes + 1))
	{
		command = commands_list->content;
		pids[i] = fork();
		if (pids[i] < 0)
			return (return_with_error("Fork failed."));
		else if (pids[i] == 0) {
			set_up_fds(command, pipe_fd, num_pipes, i);
		}
		// if (command->exit_code == EXIT_FAILURE)
		// 	return (command->exit_code);
		i++;
		commands_list = commands_list->next;
	}
	return (command->exit_code);
}

int	ft_pipe(t_list *commands_list, int num_pipes)
{
	int	**pipe_fd;
	int	*pids;
	int	exit_code;

	pipe_fd = initialize_pipe_fds(num_pipes);
	pids = (int *) malloc (sizeof(int) * (num_pipes + 1));
	if (pids == NULL)
		return (1);
	create_pipes(num_pipes, pipe_fd);
	exit_code = ft_fork(commands_list, pipe_fd, num_pipes, pids);
	close_fds(num_pipes, pipe_fd);
	wait_processes(num_pipes, pids);
	free_pipe_fds(pipe_fd, num_pipes);
	free(pids);
	return (exit_code);
}
