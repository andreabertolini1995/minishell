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

t_token	*create_token(char *str, int type, t_list *env)
{
	t_token	*token;

	token = (t_token *) malloc (sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->content = str;
	token->type = type;
	token->env = env;
	return (token);
}

t_command	*create_command(int num_args, t_list *env, int exit_code)
{
	t_command	*command;
	int			i;

	command = (t_command *) malloc (sizeof(t_command));
	if (command == NULL)
		return (NULL);
	command->cmd = NULL;
	command->num_args = num_args;
	command->args = (char **) malloc (sizeof(char *) * num_args);
	if (command->args == NULL)
		return (NULL);
	i = 0;
	while (i < num_args)
	{
		command->args[i] = NULL;
		i++;
	}
	command->operator = NULL;
	command->infile_redirect = NULL;
	command->outfile_redirect = NULL;
	command->infile = NULL;
	command->outfile = NULL;
	command->env = env;
	command->exit_code = exit_code;
	return (command);
}

t_env	*create_env_var(char *name, char *value)
{
	t_env	*env_var;

	env_var = (t_env *) malloc (sizeof(t_env));
	if (env_var == NULL)
		return (NULL);
	env_var->name = ft_strdup(name);
	if (env_var->name == NULL)
	{
		free(env_var);
		return (NULL);
	}
	env_var->value = ft_strdup(value);
	if (env_var->value == NULL)
	{
		free(env_var->name);
		free(env_var);
		return (NULL);
	}
	return (env_var);
}
