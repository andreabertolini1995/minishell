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
			i++;
	}
	return (cmd_path);
}

void	execute_cmd(t_command *command, char **argv, char *envp[2])
{
	char	*path;
	char	*cmd_path;
	char	**sub_paths;

	if (command->infile != NULL)
		redirect_input(command);
	if (command->outfile != NULL)
		redirect_output(command);
	if (is_same_string("/bin/", command->cmd))
		cmd_path = command->cmd;
	else
	{
		path = ft_getenv(command->env, "PATH");
		if (path == NULL)
		{
			print_error_msg(command->cmd, NO_FILE_OR_DIR);
			return ;
		}
		sub_paths = ft_split(path, ':');
		cmd_path = get_cmd_path(command, sub_paths);
		free_str(sub_paths);
		//free(path);
	}
	if (execve(cmd_path, argv, envp) < 0)
	{
		if (ft_strlen(command->cmd) > 0)
		{
			print_error_msg(command->cmd, CMD_NOT_FOUND);
			exit(EXIT_CMD_NOT_FOUND);
		}
	}
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
