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

static char	*create_word(char *cmd, int length, int i)
{
	char	*word;
	int		j;

	word = (char *) malloc (sizeof(char) * (length + 1));
	if (word == NULL)
		return (NULL);
	j = 0;
	while (length > 0)
	{
		word[j] = cmd[i - length];
		length--;
		j++;
	}
	word[j] = '\0';
	return (word);
}

static char	*check_if_env(char *word, t_list *env)
{
	int		i;
	char	*env_var;

	i = 0;
	while (word[i + 1] != '\0')
	{
		if (word[i] == '$' && word[i + 1] != '?')
		{
			env_var = ft_getenv(env, &word[i + 1]);
			if (env_var != NULL)
			{
				free(word);//added this
				return (env_var);
			}
		}
		i++;
	}
	if (word[0] == '$' && ft_strlen(word) > 1)
	{
		if (word[1] != '?' && word[1] != ' ' && word[1] != '\t')
		{
			if (ft_getenv(env, ft_split(word, '$')[1]) == NULL)
				return ("");
		}		
	}
	return (word);
}

int	check_for_word_without_quotes(char *cmd, int i,
		t_list **tokens_list, t_list *env)
{
	int		length;
	char	*word;

	length = calculate_word_length(cmd, i, false);
	i = i + length;
	if (length > 0)
	{
		word = create_word(cmd, length, i);
		word = check_if_env(word, env);
		ft_lstadd_back(tokens_list, ft_lstnew(create_token(word, WORD, env)));
	}
	return (i);
}

int	check_for_word_in_single_quotes(char *cmd, int i,
			t_list **tokens_list, t_list *env)
{
	int		length;
	char	*word;

	length = 0;
	while (cmd[i] != '\'' && cmd[i] != '\0')
	{
		length++;
		i++;
	}
	if (length > 0)
	{
		word = create_word(cmd, length, i);
		ft_lstadd_back(tokens_list, ft_lstnew(create_token(word, WORD, env)));
	}
	i++;
	return (i);
}

int	check_for_word_in_double_quotes(char *cmd, int i,
			t_list **tokens_list, t_list *env)
{
	int		length;
	char	*word;

	while (cmd[i] != '"' && cmd[i] != '\0')
	{
		length = calculate_word_length(cmd, i, true);
		i = i + length;
		if (length > 0)
		{
			word = create_word(cmd, length, i);
			word = check_if_env(word, env);
			ft_lstadd_back(tokens_list, ft_lstnew(create_token(word, WORD, env)));
		}
		i = check_for_spaces(cmd, i, tokens_list, env);	
	}
	i++;
	return (i);
}
