/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:33:54 by abertoli          #+#    #+#             */
/*   Updated: 2023/12/17 11:37:28 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	redirect_output(t_command *command)
{
	int	file;

	if (!ft_strncmp(command->outfile_redirect, ">>", ft_strlen(">>")))
		file = open(command->outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
	else
		file = open(command->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
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

static void	write_to_line(int file, char *line)
{
	if (line != NULL)
	{
		write(file, line, ft_strlen(line));
		write(file, "\n", 1);
		free(line);
	}
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
		write_to_line(file, line);
	}
	infile_redirect(command->infile);
	unlink(command->infile);
	close(file);
}

void	redirect_input(t_command *command)
{
	if (!ft_strncmp(command->infile_redirect, "<<", ft_strlen("<<")))
		launch_heredoc(command);
	else
		infile_redirect(command->infile);
}
