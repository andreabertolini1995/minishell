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

void	print_error_msg(char *str, int msg_type)
{
	if (msg_type == CMD_NOT_FOUND)
		printf("minishell: %s: command not found\n", str);
	else if (msg_type == NO_FILE_OR_DIR)
		printf("minishell: %s: No such file or directory\n", str);
	else if (msg_type == NUM_ARG_REQUIRED)
		printf("minishell: exit: %s: numeric argument required\n", str);
	else if (msg_type == TOO_MANY_ARGS)
		printf("minishell: exit: too many arguments\n");
	else if (msg_type == NOT_VALID_IDENTIFIER)
		printf("minishell: export: '%s': not a valid identifier\n", str);
}

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

static void	print_word(char *word)
{
	int	i;

	i = 0;
	while (word[i] != '\0')
	{
		if (word[i] == ';')
		{
			if (i > 0)
				printf("\n");
			if ((int)word[i + 1] != 0)
				print_error_msg(word + i + 1, CMD_NOT_FOUND);
			return ;
		}
		if (word[i] != '\\')
			printf("%c", word[i]);
		i++;
	}
}

int	ft_echo(t_command *command)
{
	int		i;
	bool	new_line;

	i = 0;
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
	while (i < command->num_args)
	{
		if (is_same_string("$?", command->args[i]))
			print_exit_code(command);
		else
			print_word(command->args[i]);
		i++;
	}
	if (new_line == true)
		printf("\n");
	return (EXIT_SUCCESS);
}
