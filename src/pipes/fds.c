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

int	**initialize_pipe_fds(int num_pipes)
{
	int	**pipe_fd;
	int	i;

	pipe_fd = (int **) malloc (sizeof(int *) * num_pipes);
	if (pipe_fd == NULL)
		return (NULL);
	i = 0;
	while (i < num_pipes)
	{
		pipe_fd[i] = (int *) malloc (sizeof(int) * 2);
		if (pipe_fd[i] == NULL)
			return (NULL);
		i++;
	}
	return (pipe_fd);
}

void	set_up_fds(t_command *command, int **pipe_fd, int num_pipes, int i)
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
	execute(command);
	exit(EXIT_SUCCESS);
}

void	free_pipe_fds(int **pipe_fd, int num_pipes)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		free(pipe_fd[i]);
		i++;
	}
	free(pipe_fd);
}

void	close_fds(int num_pipes, int **pipe_fd)
{
	int	i;

	i = 0;
	while (i < num_pipes)
	{
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		i++;
	}
}
