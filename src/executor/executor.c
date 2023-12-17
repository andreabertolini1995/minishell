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

static char	*combine_cmd_path(char *cmd, char *path)
{
	char	*cmd_path;
	char	*temp;

	temp = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(temp, cmd);
	free(temp);
	return (cmd_path);
}

char	*get_cmd_path(t_command *command, char **sub_paths)
{
	int		i;
	char	*cmd_path;

	i = 0;
	cmd_path = NULL;
	while (sub_paths[i] != NULL)
	{
		cmd_path = combine_cmd_path(command->cmd, sub_paths[i]);
		if (is_file(cmd_path))
			return (cmd_path);
		else
		{
			free(cmd_path);
			i++;
		}
	}
	return (NULL);
}

int	execute(t_command *command)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		exit_code;

	exit_code = 0;
	if (pipe(pipe_fd) == -1)
		return (return_with_error("Pipe failed."));
	pid = fork();
	if (pid < 0)
		return (return_with_error("Fork failed."));
	else if (pid == 0)
		child_process(command, pipe_fd);
	else
		exit_code = parent_process(command, pipe_fd, pid);
	return (exit_code);
}

int	executor(t_list *commands_list)
{
	t_command	*command;
	int			num_pipes;
	int			exit_code;

	num_pipes = get_num_pipes(commands_list);
	while (commands_list != NULL)
	{
		command = commands_list->content;
		if (num_pipes == 0)
			exit_code = execute(command);
		else
			exit_code = ft_pipe(commands_list, num_pipes);
		commands_list = update_commands_list(commands_list, num_pipes);
	}
	return (exit_code);
}
