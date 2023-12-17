/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:33:54 by abertoli          #+#    #+#             */
/*   Updated: 2023/12/17 11:36:51 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*calc_initial_cmd(t_list **tokens_list)
{
	t_token	*token;

	if ((*tokens_list) != NULL && ft_lstsize(*tokens_list) > 0)
	{
		token = (*tokens_list)->content;
		return (token->content);
	}
	return (NULL);
}

/* 
Function to calculate the length of a word within no quotes.
Special checks have been added to support exporting of environmental
variables whose value is within double quotes.
*/
static int	calculate_word_without_quotes_length(t_list **tokens_list,
				char *cmd)
{
	int		length;
	char	*initial_cmd;

	length = 0;
	initial_cmd = calc_initial_cmd(tokens_list);
	if (*cmd == '$' && *(cmd + 1) == '?')
		return (2);
	while (*cmd != '|' && *cmd != '>' && *cmd != '<'
		&& *cmd != '\t' && *cmd != '\'' && *cmd != '\0')
	{
		if (*cmd == '"' && (!is_same_string("export", initial_cmd)
				|| !is_there_second_double_quote(cmd)))
			break ;
		if (*cmd == ' ' && (!is_same_string("export", initial_cmd)))
			break ;
		if (*cmd == '$' && ft_strlen(cmd) == 1)
			return (1);
		length++;
		cmd++;
	}
	return (length);
}

static int	calculate_word_in_double_quotes_length(char *cmd)
{
	int	length;

	length = 0;
	if (*cmd == '$' && *(cmd + 1) == '?')
		return (2);
	while (*cmd != '"' && *cmd != '\0')
	{
		if (*cmd == '$')
		{
			if (length > 0)
				return (length);
			while (*cmd != '"' && *cmd != '\0'
				&& *cmd != ' ' && *cmd != '\t')
			{
				length++;
				cmd++;
			}
			return (length);
		}
		length++;
		cmd++;
	}
	return (length);
}

int	calculate_word_length(t_list **tokens_list, char *cmd, bool double_quotes)
{
	int		length;

	if (double_quotes)
		length = calculate_word_in_double_quotes_length(cmd);
	else
		length = calculate_word_without_quotes_length(tokens_list, cmd);
	return (length);
}
