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

static char	*create_word(char *cmd, int length)
{
	char	*word;
	int		j;

	word = (char *) malloc (sizeof(char) * (length + 1));
	if (word == NULL)
		return (NULL);
	j = 0;
	while (length > 0)
	{
		word[j] = *(cmd - length);
		length--;
		j++;
	}
	word[j] = '\0';
	return (word);
}

static bool	is_word_const(char *word, t_list *env)
{
	if (is_word_env(word, env) || is_word_exit_code(word, env))
		return (true);
	return (false);
}

char	*check_for_word_without_quotes(char *cmd,
		t_list **tokens_list, t_list *env, int exit_code)
{
	int		length;
	char	*word;
	bool	is_const;

	length = calculate_word_length(tokens_list, cmd, false);
	cmd = cmd + length;
	if (length > 0)
	{
		word = create_word(cmd, length);
		is_const = is_word_const(word, env);
		word = check_if_env_or_exit_code(word, env, exit_code);
		if (is_const)
			ft_lstadd_back(tokens_list,
				ft_lstnew(create_token(word, CONST, env)));
		else
			ft_lstadd_back(tokens_list,
				ft_lstnew(create_token(word, WORD, env)));
	}
	return (cmd);
}

char	*check_for_word_in_single_quotes(char *cmd,
			t_list **tokens_list, t_list *env)
{
	int		length;
	char	*word;

	length = 0;
	while (*cmd != '\'' && *cmd != '\0')
	{
		length++;
		cmd++;
	}
	if (length > 0)
	{
		word = create_word(cmd, length);
		ft_lstadd_back(tokens_list, ft_lstnew(create_token(word, WORD, env)));
	}
	cmd++;
	return (cmd);
}

char	*check_for_word_in_double_quotes(char *cmd, t_list **tokens_list,
			t_list *env, int exit_code)
{
	int		length;
	char	*word;
	bool	is_const;

	while (*cmd != '"' && *cmd != '\0')
	{
		length = calculate_word_length(tokens_list, cmd, true);
		cmd = cmd + length;
		if (length > 0)
		{
			word = create_word(cmd, length);
			is_const = is_word_const(word, env);
			word = check_if_env_or_exit_code(word, env, exit_code);
			if (is_const)
				ft_lstadd_back(tokens_list,
					ft_lstnew(create_token(word, CONST, env)));
			else
				ft_lstadd_back(tokens_list,
					ft_lstnew(create_token(word, WORD, env)));
		}
		cmd = check_for_spaces(cmd, tokens_list, env);
	}
	cmd++;
	return (cmd);
}
