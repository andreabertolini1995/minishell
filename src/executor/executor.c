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

	cmd_path = ft_strjoin(path, "/");
	cmd_path = ft_strjoin(cmd_path, cmd);
	return (cmd_path);
}

char	*get_cmd_path(t_command *command, char **sub_paths)
{
	int		i;
	char	*cmd_path;

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

void	execute_cmd(t_command *command, char **argv, char *envp[2])
{
	char	*path;
	char	*cmd_path;
	char	**sub_paths;

	if (command->outfile != NULL)
		redirect_output(command);
	if (command->infile != NULL)
		redirect_input(command);
	if (is_same_string("/bin/", command->cmd))
		cmd_path = command->cmd;
	else
	{
		path = getenv("PATH");
		sub_paths = ft_split(path, ':');
		cmd_path = get_cmd_path(command, sub_paths);
	}
	if (execve(cmd_path, argv, envp) < 0)
	{
		perror(command->cmd);
		free(argv);
		free(cmd_path);
		exit(EXIT_FAILURE);
	}
	free(cmd_path);
}

int	execute(t_command *command)
{
	int		pipe_fd[2];
	pid_t	pid;
	int		wstatus;
	int		exit_code;

	exit_code = 0;
	if (pipe(pipe_fd) == -1)
		return (return_with_error("Pipe failed."));
	pid = fork();
	if (pid < 0)
		return (return_with_error("Fork failed."));
	else if (pid == 0)
		exit_code = child_process(command, pipe_fd);
	else
	{
		if (is_builtin(command->cmd))
			exit_code = execute_builtin_parent(command, pipe_fd);
		waitpid(pid, &wstatus, 0);
		if (!is_builtin(command->cmd))
		{
			if (WIFEXITED(wstatus))
				exit_code = WEXITSTATUS(wstatus);
		}
		close(pipe_fd[0]);
	}
	return (exit_code);
}

int	executor(t_list *commands_list, int exit_code)
{
	t_command	*command;
	int			num_pipes;

	num_pipes = get_num_pipes(commands_list);
	while (commands_list != NULL)
	{
		command = commands_list->content;
		command->exit_code = exit_code;
		if (num_pipes == 0)
			exit_code = execute(command);
		else
			exit_code = ft_pipe(commands_list, num_pipes);
		commands_list = update_commands_list(commands_list, num_pipes);
	}
	return (exit_code);
}
