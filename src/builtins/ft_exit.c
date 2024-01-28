/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:33:54 by abertoli          #+#    #+#             */
/*   Updated: 2023/12/17 11:35:17 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*remove_quotes_from_str(char *str)
{
	char	*new_str;
	int		i;
	int		j;

	new_str = (char *) malloc (sizeof(char) * (ft_strlen(str) + 1));
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
	new_str[j] = '\0';
	return (new_str);
}

static void	combine_args_to_exit_code(t_command *command)
{
	char	*temp;
	int		exit_code;

	temp = ft_strjoin(command->args[0], command->args[1]);
	exit_code = ft_atoi(remove_quotes_from_str(temp));
	free(temp);
	exit(exit_code);
}

static void	deal_single_argument(t_command *command,
				int *pipe_fd, int signal_to_send)
{
	char	*arg_str;

	arg_str = remove_quotes_from_str(command->args[0]);
	if (ft_atoi(arg_str) == 0)
		print_error_msg(command->args[0], NUM_ARG_REQUIRED);
	free(arg_str);
	write(pipe_fd[1], &signal_to_send, sizeof(int));
	close(pipe_fd[1]);
}

int	ft_exit_child(t_command *command, int *pipe_fd)
{
	int		signal_to_send;

	signal_to_send = SIGINT;
	printf("exit\n");
	if (command->num_args == 1)
		deal_single_argument(command, pipe_fd, signal_to_send);
	else if (command->num_args > 1)
	{
		if (is_same_string(command->args[0], "-")
			|| is_same_string(command->args[0], "+"))
			combine_args_to_exit_code(command);
		else
		{
			print_error_msg(command->cmd, TOO_MANY_ARGS);
			return (EXIT_FAILURE);
		}
	}
	else
	{
		write(pipe_fd[1], &signal_to_send, sizeof(int));
		close(pipe_fd[1]);
	}
	return (EXIT_SUCCESS);
}

int	ft_exit_parent(t_command *command, int *pipe_fd)
{
	int		signal_from_child;
	int		exit_code;

	close(pipe_fd[1]);
	read(pipe_fd[0], &signal_from_child, sizeof(int));
	close(pipe_fd[0]);
	if (command->num_args == 1)
	{
		exit_code = ft_atoi(remove_quotes_from_str(command->args[0]));
		if (exit_code == 0)
			exit(NO_FILE_OR_DIR);
		else
			exit(exit_code);
	}
	else if (command->num_args > 1)
	{
		if (is_same_string(command->args[0], "-")
			|| is_same_string(command->args[0], "+"))
			combine_args_to_exit_code(command);
		else 
			return (EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}
