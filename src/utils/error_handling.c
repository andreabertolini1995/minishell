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

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

void	print_error_msg(char *str, int msg_type)
{
	ft_putstr_fd("minishell: ", 1);
	ft_putstr_fd(str, 1);
	ft_putstr_fd(": ", 1);
	if (msg_type == CMD_NOT_FOUND)
		ft_putstr_fd("command not found\n", 2);
	else if (msg_type == NO_FILE_OR_DIR)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (msg_type == NUM_ARG_REQUIRED)
		ft_putstr_fd("numeric argument required\n", 2);
	else if (msg_type == TOO_MANY_ARGS)
		ft_putstr_fd("too many arguments\n", 2);
	else if (msg_type == NOT_VALID_IDENTIFIER)
		ft_putstr_fd("not a valid identifier\n", 2);
}
