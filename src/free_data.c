/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <eltongid@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:19:57 by eltongid          #+#    #+#             */
/*   Updated: 2023/12/17 11:38:20 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_tokens(t_list *tokens_list)
{
	t_list	*tmp;
	t_token	*token;

	while (tokens_list != NULL)
	{
		tmp = tokens_list->next;
		token = tokens_list->content;
		if (token->type == WORD)
			free(token->content);
		free(token);
		free(tokens_list);
		tokens_list = tmp;
	}
}

void	free_env_var(t_env *env_var)
{
	if (env_var != NULL)
	{
		free(env_var->name);
		free(env_var->value);
		free(env_var);
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
		free_env_var(env);
		free(env_list);
		env_list = tmp;
	}
}

void	free_command(t_command *command)
{
	int	i;

	i = 0;
	free_env(command->env);
	if (command != NULL)
	{
		free(command->cmd);
		free(command->operator);
		free(command->outfile_redirect);
		free(command->infile_redirect);
		free(command->infile);
		free(command->outfile);
	}
	if (command->args != NULL)
	{
		while (i < command->num_args)
		{
			free(command->args[i]);
			i++;
		}
		free(command->args);
	}
	free(command);
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
