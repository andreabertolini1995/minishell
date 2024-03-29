/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <eltongid@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:19:57 by eltongid          #+#    #+#             */
/*   Updated: 2023/12/17 11:37:13 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	calc_num_args(t_list *tokens_list, t_token *token, char *cmd)
{
	int	num_args;

	num_args = 0;
	while ((token->type == WORD || token->type == CONST
			|| token->type == EMPTY) && tokens_list != NULL)
	{
		if (token->type == WORD || token->type == CONST
			|| (is_same_string(cmd, "echo")))
			num_args++;
		tokens_list = tokens_list->next;
		if (tokens_list != NULL)
			token = tokens_list->content;
	}
	return (num_args);
}

int	ft_num_args(t_list *tokens_list)
{
	t_token	*token;
	char	*cmd;
	int		list_size;
	int		num_args;

	if (tokens_list == NULL)
		return (0);
	list_size = ft_lstsize(tokens_list);
	token = tokens_list->content;
	cmd = token->content;
	if (token->type != WORD && token->type != CONST)
		return (0);
	num_args = calc_num_args(tokens_list, token, cmd);
	if (is_same_string(cmd, "echo") && list_size > 1)
		return (num_args - 2);
	else
		return (num_args - 1);
}

t_token	*update_tokens_list(t_list **tokens_list, t_token *token)
{
	while (token->type == EMPTY && (*tokens_list) != NULL)
	{
		(*tokens_list) = (*tokens_list)->next;
		if ((*tokens_list) != NULL)
			token = (*tokens_list)->content;
	}
	return (token);
}

bool	is_blocking_command(t_command *command)
{
	if (command->cmd != NULL)
	{
		if ((is_same_string(command->cmd, "cat")
				&& command->num_args == 0)
			|| (is_same_string(command->cmd, "grep")
				&& command->num_args > 0)
			|| (is_same_string(command->cmd, "wc")
				&& command->num_args == 0))
			return (true);
	}
	return (false);
}

void	free_str(char **str)
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
