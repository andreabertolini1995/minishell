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

/* 
Function to calculate the length of a word within no quotes.
Special checks have been added to support exporting of environmental
variables whose value is within double quotes.
*/
int	calculate_word_without_quotes_length(char *cmd, int i)
{
	int length;

	length = 0;
	if (ft_strlen(cmd) > 1)
	{
		if (cmd[i] == '$' && cmd[i + 1] == '?')
			return (2);
	}
	while (cmd[i] != '|' && cmd[i] != '>' && cmd[i] != '<'
		&& cmd[i] != '\t' && cmd[i] != '\'' && cmd[i] != '\0')
	{
		if (cmd[i] == '"' && (!is_same_string("export", cmd)
			|| !is_there_second_double_quote(cmd, i)))
			break ;
		if (cmd[i] == ' ' && (!is_same_string("export", cmd)
			|| (i == (int)ft_strlen("export"))))
			break ;
		if (cmd[i] == '$' && ft_strlen(cmd) == 1)
			return (1);
		length++;
		i++;
	}
	return (length);
}

int	calculate_word_in_double_quotes_length(char *cmd, int i)
{
	int length;

	length = 0;
	if (ft_strlen(cmd) > 1)
	{
		if (cmd[i] == '$' && cmd[i + 1] == '?')
			return (2);
	}
	while (cmd[i] != '"' && cmd[i] != '\0')
	{
		if (cmd[i] == '$')
		{
			if (length > 0)
				return (length);
			while (cmd[i] != '"' && cmd[i] != '\0'
				&& cmd[i] != ' ' && cmd[i] != '\t')
			{
				length++;
				i++;
			}
			return (length);
		}
		length++;
		i++;
	}
	return (length);
}

int	calculate_word_length(char *cmd, int i, bool double_quotes)
{
	int length;
	
	if (double_quotes)
		length = calculate_word_in_double_quotes_length(cmd, i);
	else
		length = calculate_word_without_quotes_length(cmd, i);
	return (length);
}
