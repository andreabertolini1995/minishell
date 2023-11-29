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

static bool	is_there_second_single_quote(char *cmd, int i)
{
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '\'')
			return (true);
		i++;
	}
	return (false);
}

static bool	is_there_second_double_quote(char *cmd, int i)
{
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '"')
			return (true);
		i++;
	}
	return (false);
}

static int	check_for_word(char *cmd, int i, t_list **tokens_list, t_list *env)
{
	if (cmd[i] == '\'')
	{
		if (is_there_second_single_quote(cmd, i))
			i = check_for_word_in_single_quotes(cmd, i + 1, tokens_list, env);
		else
			i = check_for_word_without_quotes(cmd, i, tokens_list, env);
	}
	else if (cmd[i] == '"')
	{
		if (is_there_second_double_quote(cmd, i))
			i = check_for_word_in_double_quotes(cmd, i + 1, tokens_list, env);
		else
			i = check_for_word_without_quotes(cmd, i, tokens_list, env);
	}
	else
		i = check_for_word_without_quotes(cmd, i, tokens_list, env);
	return (i);
}

int	check_for_spaces(char *cmd, int i,
			t_list **tokens_list, t_list *env)
{
	if (cmd[i] == ' ')
		ft_lstadd_back(tokens_list,
			ft_lstnew(create_token(" ", EMPTY, env)));
	else if (cmd[i] == '\t')
		ft_lstadd_back(tokens_list,
			ft_lstnew(create_token("\t", EMPTY, env)));
	while (cmd[i] == ' ' || cmd[i] == '\t')
			i++;
	return (i);
}

t_list	*lexer(char *cmd, t_list *env)
{
	size_t	i;
	t_list	*tokens_list;

	i = 0;
	tokens_list = NULL;
	while (cmd[i] != '\0')
	{
		if (cmd[i] == '|')
		{
			ft_lstadd_back(&tokens_list,
				ft_lstnew(create_token("|", PIPE, env)));
			i++;
		}
		i = check_for_redirections(cmd, i, &tokens_list, env);
		i = check_for_word(cmd, i, &tokens_list, env);
		i = check_for_spaces(cmd, i, &tokens_list, env);
		// Keep commented out to check this removal doens't break something else
		// if (cmd[i] != '\0' && cmd[i] != '\''
		// 	&& cmd[i] != '"' && cmd[i] != ' ' && cmd[i] != '\t')
		// 	i++;
	}
	return (tokens_list);
}
