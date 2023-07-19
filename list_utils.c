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

#include "minishell.h"

void	add_cmd_back(t_command **lst, t_command *new)
{
	t_command	*last_node;

	if ((*lst) == NULL)
	{
		new->next = NULL;
		*lst = new;
	}
	else
	{
		last_node = last_cmd(*lst);
		last_node->next = new;
	}
}

t_command	*last_cmd(t_command *lst)
{
	t_command	*last_node;

	if (lst == NULL)
		last_node = NULL;
	while (lst != NULL)
	{
		last_node = lst;
		lst = lst->next;
	}
	return (last_node);
}
