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

int	execute_builtin_child(t_command *command, int *pipe_fd)
{
	int	signal_to_send;
	int	exit_code;

	exit_code = 0;
	if (command->infile != NULL)
		redirect_input(command);
	if (command->outfile != NULL)
		redirect_output(command);
	if (is_same_string(command->cmd, "echo"))
		exit_code = ft_echo(command);
	else if (is_same_string(command->cmd, "pwd"))
		exit_code = ft_pwd();
	else if (is_same_string(command->cmd, "env"))
		exit_code = ft_env(command, "env");
	else if (is_same_string(command->cmd, "exit"))
	{
		signal_to_send = SIGINT;
		printf("exit\n");
		write(pipe_fd[1], &signal_to_send, sizeof(int));
		close(pipe_fd[1]);
	}
	else if (is_same_string(command->cmd, "clear"))
		exit_code = clear();
	return (exit_code);
}

int	execute_builtin_parent(t_command *command, int *pipe_fd)
{
	int	signal_from_child;
	int	exit_code;

	exit_code = 0;
	if (is_same_string(command->cmd, "cd"))
		exit_code = ft_cd(command);
	else if (is_same_string(command->cmd, "export"))
		exit_code = ft_export(command);
	else if (is_same_string(command->cmd, "unset"))
		exit_code = ft_unset(command);
	else if (is_same_string(command->cmd, "exit"))
	{
		close(pipe_fd[1]);
		read(pipe_fd[0], &signal_from_child, sizeof(int));
		if (signal_from_child == SIGINT)
		{
			close(pipe_fd[0]);
			if (command->num_args == 1)
				exit(ft_atoi(command->args[0]));
			else
				exit(EXIT_SUCCESS);
		}
	}
	return (exit_code);
}

static char	**fill_argv(t_command *command)
{
	char	**argv;
	int		i;

	argv = (char **) malloc (sizeof(char *) * (command->num_args + 2));
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

void	child_process(t_command *command, int *pipe_fd)
{
	char	**argv;
	char	*envp[2];

	argv = fill_argv(command);
	envp[0] = NULL;
	close(pipe_fd[0]);
	if (is_builtin(command->cmd))
	{
		command->exit_code = execute_builtin_child(command, pipe_fd);
		close(pipe_fd[1]);
		free_argv(argv);
		exit(command->exit_code);
	}
	else
		execute_cmd(command, argv, envp);
}

int	parent_process(t_command *command, int *pipe_fd, pid_t pid)
{
	int		wstatus;
	int		exit_code;

	if (is_builtin(command->cmd))
		exit_code = execute_builtin_parent(command, pipe_fd);
	waitpid(pid, &wstatus, 0);
	if (!is_builtin(command->cmd))
	{
		if (WIFEXITED(wstatus))
			exit_code = WEXITSTATUS(wstatus);
	}
	return (exit_code);
}
