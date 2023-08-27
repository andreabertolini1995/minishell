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

	word = (char *) malloc (sizeof(char) * length);
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

static char	*check_if_env(char *word)
{
	int	i;

	i = 0;
	while (word[i + 1] != '\0')
	{
		if (word[i] == '$' && word[i + 1] != '?')
		{
			word += (i + 1);
			return (getenv(word));
		}
		i++;
	}
	return (word);
}

int	check_for_word_in_single_quotes(char *cmd, int i, t_list **tokens_list)
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
		ft_lstadd_back(tokens_list, ft_lstnew(create_token(word, WORD)));
	}
	return (i);
}

int	check_for_word_in_double_quotes(char *cmd, int i, t_list **tokens_list)
{
	int		length;
	char	*tmp_word;
	char	*final_word;
	int		start;

	start = i;
	while (cmd[i] != '"' && cmd[i] != '\0')
	{
		length = 0;
		while (cmd[i] != '"' && cmd[i] != ' '
			&& cmd[i] != '\t' && cmd[i] != '\0')
		{
			length++;
			i++;
		}
		tmp_word = create_word(cmd, length, i);
		tmp_word = check_if_env(tmp_word);
		if ((i - length) > start)
			final_word = ft_strjoin("", " ");
		final_word = ft_strjoin(final_word, tmp_word);
		// free(tmp_word);
		i++;
	}
	ft_lstadd_back(tokens_list, ft_lstnew(create_token(final_word, WORD)));
	return (i);
}

int	check_for_word_without_quotes(char *cmd, int i, t_list **tokens_list)
{
	int		length;
	char	*word;

	length = 0;
	while (cmd[i] != '|' && cmd[i] != '>' && cmd[i] != '<'
		&& cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '\0')
	{
		length++;
		i++;
	}
	if (length > 0)
	{
		word = create_word(cmd, length, i);
		word = check_if_env(word);
		ft_lstadd_back(tokens_list, ft_lstnew(create_token(word, WORD)));
	}
	return (i);
}
