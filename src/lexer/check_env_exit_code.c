/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_env_exit_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:33:54 by abertoli          #+#    #+#             */
/*   Updated: 2023/12/16 21:21:43 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
				return (env_var);
		}
		i++;
	}
	return (NULL);
}

static int	update_exit_code(int exit_code)
{
	if (g_signal_num == SIGINT)
		return (EXIT_SIGINT);
	else if (g_signal_num == SIGQUIT)
		return (EXIT_SIGQUIT);
	else
		return (exit_code);
}

static char	*check_if_exit_code(char *word, t_list *env, int exit_code)
{
	if (word[0] == '$' && ft_strlen(word) > 1)
	{
		if (word[1] != '?' && word[1] != ' ' && word[1] != '\t')
		{
			if (ft_getenv(env, word + 1) == NULL)
			{
				free (word);
				return ("");
			}
		}
		else if (word[1] == '?' && ft_strlen(word) == 2)
		{
			free (word);
			return (ft_itoa(update_exit_code(exit_code)));
		}
	}
	return (NULL);
}

char	*check_if_env_or_exit_code(char *word, t_list *env, int exit_code)
{
	char	*result;

	result = check_if_env(word, env);
	if (result != NULL)
	{
		free(word);
		return (result);
	}
	result = check_if_exit_code(word, env, exit_code);
	if (result != NULL)
		return (result);
	return (word);
}

bool	is_word_env(char *word, t_list *env)
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
				free(env_var);
				return (true);
			}
		}
		i++;
	}
	return (false);
}
