/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <eltongid@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:18:46 by eltongid          #+#    #+#             */
/*   Updated: 2023/12/16 21:18:51 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_all(t_command *command, char **argv, char *path)
{
	if (is_same_string(command->cmd, path))
		print_error_msg(command->cmd, NO_FILE_OR_DIR);
	else
		print_error_msg(command->cmd, CMD_NOT_FOUND);
	free_command(command);
	free_argv(argv);
	free(path);
	exit (EXIT_CMD_NOT_FOUND);
}

static void	check_redirect(t_command *command)
{
	if (command->infile != NULL)
		redirect_input(command);
	if (command->outfile != NULL)
		redirect_output(command);
}

void	execute_cmd(t_command *command, char **argv, char *envp[2])
{
	char	*path;
	char	*cmd_path;
	char	**sub_paths;

	path = NULL; // needs to be initialised for /bin/ls/wrong/command
	check_redirect(command);
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
	}
	if (cmd_path == NULL)
		free_all(command, argv, path);
	if (execve(cmd_path, argv, envp) < 0)
		exit_program(command, path);
}
