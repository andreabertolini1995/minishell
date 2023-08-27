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

bool	is_file(char *path_cmd)
{
	if (access(path_cmd, F_OK) == 0)
		return (true);
	else
		return (false);
}

bool	is_same_string(char *str1, char *str2)
{
	if (!ft_strncmp(str1, str2, ft_strlen(str1)))
		return (true);
	else
		return (false);
}

bool	is_infile_redirection(char *cmd)
{
	if (is_same_string(cmd, "<")
		|| is_same_string(cmd, "<<"))
		return (true);
	else
		return (false);
}

bool	is_pipe(char *cmd)
{
	if (is_same_string(cmd, "|"))
		return (true);
	else
		return (false);
}

bool	is_outfile_redirection(char *cmd)
{
	if (is_same_string(cmd, ">")
		|| is_same_string(cmd, ">>"))
		return (true);
	else
		return (false);
}
