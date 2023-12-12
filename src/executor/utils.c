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

void	exit_program(t_command *command, char *path, char **argv)
{
	if (ft_strlen(command->cmd) > 0)
	{
		if (is_same_string(command->cmd, path))
			print_error_msg(command->cmd, NO_FILE_OR_DIR);
		else
			print_error_msg(command->cmd, CMD_NOT_FOUND);
		free_command(command);
		free_argv(argv);
		free(path);
		exit(EXIT_CMD_NOT_FOUND);
	}
}

void	free_argv(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

bool	is_builtin(char *cmd)
{
	if (cmd != NULL)
	{
		if (is_same_string(cmd, "pwd")
			|| is_same_string(cmd, "env")
			|| is_same_string(cmd, "echo")
			|| is_same_string(cmd, "exit")
			|| is_same_string(cmd, "cd")
			|| is_same_string(cmd, "export")
			|| is_same_string(cmd, "unset")
			|| is_same_string(cmd, "clear"))
			return (true);
		else
			return (false);
	}
	return (false);
}

t_list	*update_commands_list(t_list *commands_list, int num_pipes)
{
	int	i;

	if (commands_list == NULL)
		return (NULL);
	if (num_pipes > 0)
	{
		i = 0;
		while (i < (num_pipes + 1) && commands_list != NULL)
		{
			commands_list = commands_list->next;
			i++;
		}
	}
	else
		commands_list = commands_list->next;
	return (commands_list);
}

int	wait_processes(int num_pipes, pid_t *pids)
{
	int	i;
	int	wstatus;
	int	last_exit_status;

	i = 0;
	wstatus = 0;
	while (i < (num_pipes + 1))
	{
		if (waitpid(pids[i], &wstatus, 0) == -1)
			return (return_with_error("Not implemented :)"));
		if (WIFEXITED(wstatus))
		{
			if (i == num_pipes)
				last_exit_status = WEXITSTATUS(wstatus);
		}
		i++;
	}
	return (last_exit_status);
}
