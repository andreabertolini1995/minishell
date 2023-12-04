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

void free_str(char **str)
{
	int	i;

	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_tokens(t_list *tokens_list)
{
	t_list	*tmp;
	t_token	*token;

	while (tokens_list != NULL)
	{
		tmp = tokens_list->next;
		token = tokens_list->content;
		//Check if this causes issues - if the word belongs to the env // to check this run command echo $PATH for example. 
		if (token->type == WORD)
			free(token->content);
		free(token);
		free(tokens_list);
		tokens_list = tmp;
	}
}

void	free_env(t_list *env_list)
{
	t_list	*tmp;
	t_env	*env;

	while (env_list != NULL)
	{
		tmp = env_list->next;
		env = env_list->content;
		free(env->name);
		free(env->value);
		free(env);
		free(env_list);
		env_list = tmp;
	}
}

void	free_commands(t_list *commands_list)
{
	t_list		*tmp;
	t_command	*command;
	int			i;

	while (commands_list != NULL)
	{
		tmp = commands_list->next;
		command = commands_list->content;
		i = 0;
		while (i < command->num_args)
		{
			free(command->args[i]);
			i++;
		}
		free(command->args);
		free(command->cmd);
		free(command->infile);
		free(command->outfile);
		free(command->operator);
		free(command);
		free(commands_list);
		commands_list = tmp;
	}
}

