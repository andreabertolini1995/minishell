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
	int	j;

	pipe_fd = (int **) malloc (sizeof(int *) * num_pipes + 1);
	if (pipe_fd == NULL)
		return (NULL);
	i = 0;
	while (i < num_pipes)
	{
		pipe_fd[i] = (int *) malloc (sizeof(int) * 2);
		if (pipe_fd[i] == NULL)
		{
			j = -1;
			while (++j < i)
				free(pipe_fd[j]);
			free(pipe_fd);
			return (NULL);
		}
		i++;
	}
	return (pipe_fd);
}

void set_up_fds(int **pipe_fd, int num_pipes, int i)
{
	int res;

	res = -1;
	if (i == 0)
	{
		res = dup2(pipe_fd[i][1], STDOUT_FILENO);
		if (res < 0)
			return_with_error("dup2 failed");
		close(pipe_fd[i][0]);
		close(pipe_fd[i][1]);
		printf("process %d closed pipe %d\n", getpid(), *pipe_fd[i]);  //read end
	}
	else if (i > 0 && i < num_pipes)
	{
		res = dup2(pipe_fd[i - 1][0], STDIN_FILENO);
		if (res < 0)
			return_with_error("dup2 failed");
		res = dup2(pipe_fd[i][1], STDOUT_FILENO);
		if (res < 0)
			return_with_error("dup2 failed");
		close(pipe_fd[i - 1][1]); //write end of previous pipe
		close(pipe_fd[i][0]);	//read end of current pipe
	}
	else if (i == num_pipes)
	{
		res = dup2(pipe_fd[i - 1][0], STDIN_FILENO);
		if (res < 0)
			return_with_error("dup2 failed");
		close(pipe_fd[i - 1][1]);  //write end of last pipe
	}
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
