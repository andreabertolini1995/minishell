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

int	ft_num_args(t_list *tokens_list)
{
	int		num_args;
	t_token	*token;
	char	*cmd;
	int		list_size;

	list_size = ft_lstsize(tokens_list);
	num_args = 0;
	token = tokens_list->content;
	cmd = token->content;
	if (token->type != WORD)
		return (0); // hardcoded for << 
	while ((token->type == WORD || token->type == EMPTY) && tokens_list != NULL)
	{
		if (token->type == WORD || (is_same_string(cmd, "echo")))
			num_args++;
		tokens_list = tokens_list->next;
		if (tokens_list != NULL)
			token = tokens_list->content;
	}
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
