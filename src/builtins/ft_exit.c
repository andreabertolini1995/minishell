
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

char	*remove_quotes_from_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = (char *) malloc (sizeof(char) * (ft_strlen(str)));
	if (new_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '\'' && str[i] != '"')
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	return (new_str);
}

void	ft_exit_child(t_command *command, int *pipe_fd)
{
	int		signal_to_send;
	char	*arg_str;

	signal_to_send = SIGINT;
	printf("exit\n");
	if (command->num_args == 1)
	{
		arg_str = remove_quotes_from_str(command->args[0]);
		if (ft_atoi(arg_str) == 0)
			printf("minishell: exit: %s: numeric argument required\n",
				command->args[0]);
		free(arg_str);
		write(pipe_fd[1], &signal_to_send, sizeof(int));
		close(pipe_fd[1]);
	}
	else if (command->num_args > 1)
		printf("minishell: exit: too many arguments\n");
	else
	{
		write(pipe_fd[1], &signal_to_send, sizeof(int));
		close(pipe_fd[1]);
	}
	
}

void	ft_exit_parent(t_command *command, int *pipe_fd)
{
	int		signal_from_child;
	int		exit_code;

	close(pipe_fd[1]);
	read(pipe_fd[0], &signal_from_child, sizeof(int));
	close(pipe_fd[0]);
	if (signal_from_child == SIGINT)
	{
		if (command->num_args == 1)
		{
			exit_code = ft_atoi(remove_quotes_from_str(command->args[0]));
			if (exit_code == 0)
				exit(EXIT_ALPHA_ARG);
			else
				exit(exit_code);
		}
		else if (command->num_args > 1)
			exit(EXIT_FAILURE);
		else
			exit(EXIT_SUCCESS);
	}
}