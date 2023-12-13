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

void	redirect_output(t_command *command)
{
	int	file;

	if (is_same_string(command->outfile_redirect, ">"))
		file = open(command->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	else
		file = open(command->outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
	dup2(file, STDOUT_FILENO);
	close(file);
}

static void	infile_redirect(char *file_name)
{
	int	file;

	file = open(file_name, O_RDONLY);
	dup2(file, STDIN_FILENO);
	close(file);
}

static void	launch_heredoc(t_command *command)
{
	int		file;
	char	*line;

	file = open(command->infile, O_WRONLY | O_CREAT | O_APPEND, 0777);
	g_signal_num = EXIT_SUCCESS;
	signal(SIGINT, sigint_handler_heredoc);
	while (42)
	{
		line = readline("> ");
		if (!line || is_same_string(line, command->infile))
		{
			free(line);
			break ;
		}
		if (g_signal_num == SIGINT)
		{
			free(line);
			break ;
		}
		write(file, line, ft_strlen(line));
		write(file, "\n", 1);
		free(line);
	}
	infile_redirect(command->infile);
	unlink(command->infile);
	close(file);
}

void	redirect_input(t_command *command)
{
	if (is_same_string(command->infile_redirect, "<<"))
		launch_heredoc(command);
	else
		infile_redirect(command->infile);
}
