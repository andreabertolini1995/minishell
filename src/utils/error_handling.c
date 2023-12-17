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

int	return_with_error(char *error_msg)
{
	perror(error_msg);
	return (EXIT_FAILURE);
}

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
	else if (msg_type == UNEXPECTED_VALUE)
		printf("minishell: syntax error near unexpected token `newline'\n");
}
