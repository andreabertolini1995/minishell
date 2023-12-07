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

static bool	is_there_second_single_quote(char *cmd)
{
	while (*cmd != '\0')
	{
		if (*cmd == '\'')
			return (true);
		cmd++;
	}
	return (false);
}

bool	is_there_second_double_quote(char *cmd)
{
	while (*cmd != '\0')
	{
		if (*cmd == '"')
			return (true);
		cmd++;
	}
	return (false);
}

static char	*check_for_word(char *cmd, t_list **tokens_list,
			t_list *env, int exit_code)
{
	if (*cmd == '\'')
	{
		if (is_there_second_single_quote(cmd))
			cmd = check_for_word_in_single_quotes(cmd + 1, tokens_list, env);
		else
			cmd = check_for_word_without_quotes(cmd, tokens_list,
					env, exit_code);
	}
	else if (*cmd == '"')
	{
		if (is_there_second_double_quote(cmd))
			cmd = check_for_word_in_double_quotes(cmd + 1, tokens_list,
					env, exit_code);
		else
			cmd = check_for_word_without_quotes(cmd, tokens_list,
					env, exit_code);
	}
	else
		cmd = check_for_word_without_quotes(cmd, tokens_list, env, exit_code);
	return (cmd);
}

char	*check_for_spaces(char *cmd,
			t_list **tokens_list, t_list *env)
{
	if (*cmd == ' ')
		ft_lstadd_back(tokens_list,
			ft_lstnew(create_token(" ", EMPTY, env)));
	else if (*cmd == '\t')
		ft_lstadd_back(tokens_list,
			ft_lstnew(create_token("\t", EMPTY, env)));
	while (*cmd == ' ' || *cmd == '\t')
		cmd++;
	return (cmd);
}

t_list	*lexer(char *cmd, t_list *env, int exit_code)
{
	t_list	*tokens_list;

	tokens_list = NULL;
	while (*cmd != '\0')
	{
		if (*cmd == '|')
		{
			ft_lstadd_back(&tokens_list,
				ft_lstnew(create_token("|", PIPE, env)));
			cmd++;
		}
		cmd = check_for_redirections(cmd, &tokens_list, env);
		cmd = check_for_word(cmd, &tokens_list, env, exit_code);
		cmd = check_for_spaces(cmd, &tokens_list, env);
	}
	return (tokens_list);
}
