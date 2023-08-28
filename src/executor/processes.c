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

void	execute_builtin_child(t_command *command, int *pipe_fd)
{
	int	signal_to_send;

	if (is_same_string(command->cmd, "echo"))
		ft_echo(command);
	else if (is_same_string(command->cmd, "pwd"))
		ft_pwd();
	else if (is_same_string(command->cmd, "env"))
		ft_env(command, "env");
	else if (is_same_string(command->cmd, "exit"))
	{
		signal_to_send = SIGINT;
		printf("exit\n");
		write(pipe_fd[1], &signal_to_send, sizeof(int));
		close(pipe_fd[1]);
	}
	else if (is_same_string(command->cmd, "clear"))
		clear();
}

void	execute_builtin_parent(t_command *command, int *pipe_fd)
{
	int	signal_from_child;

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
		execute_builtin_child(command, pipe_fd);
	else
		execute_cmd(command, argv, envp);
	close(pipe_fd[1]);
	free_argv(argv);
	exit(1);
}

void	wait_processes(int num_pipes, int *pids)
{
	int	i;

	i = 0;
	while (i < (num_pipes + 1))
	{
		waitpid(pids[i], NULL, 0);
		i++;
	}
}
