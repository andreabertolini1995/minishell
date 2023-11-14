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

static bool	check_new_line(char *option)
{
	size_t	i;

	i = 0;
	if (option[i] != '-' && option[i + 1] != 'n')
		return (true);
	while (option[i] != '\0')
	{
		if (option[i] == '-')
			i++;
		while (option[i] == 'n')
			i++;
	}
	if (i == ft_strlen(option))
		return (false);
	return (true);
}

static void	print_exit_code(t_command *command)
{
	if (g_signal_num == SIGINT)
	{
		printf("%d", EXIT_SIGINT);
		g_signal_num = EXIT_SUCCESS;
	}
	else if (g_signal_num == SIGQUIT)
	{
		printf("%d", EXIT_SIGQUIT);
		g_signal_num = EXIT_SUCCESS;
	}
	else
		printf("%d", command->exit_code);
}

int	ft_echo(t_command *command)
{
	int		i;
	bool	new_line;

	i = 0;
	new_line = check_new_line(command->args[i]);
	if (new_line == false)
	{
		i++;
		while (!check_new_line(command->args[i])
			|| is_same_string(command->args[i], " "))
			i++;
	}
	if (is_same_string(command->args[i], "$?"))
	{
		print_exit_code(command);
		i++;
	}
	while (i < command->num_args)
	{
		printf("%s", command->args[i]);
		i++;
	}
	if (new_line == true)
		printf("\n");
	return (EXIT_SUCCESS);
}
