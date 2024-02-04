/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:33:54 by abertoli          #+#    #+#             */
/*   Updated: 2023/12/17 11:34:43 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static bool	check_new_line(char *option)
{
	size_t	i;

	i = 0;
	if (ft_strlen(option) == 0)
		return (true);
	if (option[i] != '-' || option[i + 1] != 'n')
		return (true);
	while (option[i] != '\0')
	{
		if (option[i] == '-')
			i++;
		while (option[i] == 'n')
			i++;
		break ;
	}
	if (i == ft_strlen(option))
		return (false);
	return (true);
}

static void	print_word(char *word)
{
	int	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] != '\\')
			printf("%c", word[i]);
		i++;
	}
}

static bool	is_known_exit_code(int exit_code)
{
	if (exit_code != EXIT_SUCCESS
		&& exit_code != EXIT_FAILURE
		&& exit_code != EXIT_UNEXP_VALUE
		&& exit_code != EXIT_CMD_NOT_FOUND
		&& exit_code != EXIT_SIGINT
		&& exit_code != EXIT_SIGQUIT)
		return (false);
	return (true); 
}

static void	echo_print(t_command *command, int i, bool new_line)
{
	while (i < command->num_args)
	{
		if (!is_known_exit_code(command->exit_code))
			command->args[i] = "0";
		print_word(command->args[i]);
		i++;
	}
	if (new_line == true)
		printf("\n");
}

int	ft_echo(t_command *command)
{
	int		i;
	bool	new_line;

	i = 0;
	new_line = true;
	if (command->num_args == 0)
	{
		printf("\n");
		return (EXIT_SUCCESS);
	}
	if (command->num_args > 0)
	{
		new_line = check_new_line(command->args[i]);
		if (new_line == false)
		{
			i++;
			while (!check_new_line(command->args[i])
				|| is_same_string(command->args[i], " "))
				i++;
		}
	}
	echo_print(command, i, new_line);
	return (EXIT_SUCCESS);
}
