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

void	free_argv(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] != NULL)
	{
		free(argv[i]);
		i++;
	}
	free(argv);
}

bool	is_builtin(char *cmd)
{
	if (cmd != NULL)
	{
		if (is_same_string(cmd, "pwd")
		|| is_same_string(cmd, "env")
		|| is_same_string(cmd, "echo")
		|| is_same_string(cmd, "exit")
		|| is_same_string(cmd, "cd")
		|| is_same_string(cmd, "export")
		|| is_same_string(cmd, "unset")
		|| is_same_string(cmd, "clear"))
		return (true);
		else
			return (false);
	}
	return (false);
}

t_list	*update_commands_list(t_list *commands_list, int num_pipes)
{
	int	i;

	if (num_pipes > 0)
	{
		i = 0;
		while (i < (num_pipes + 1))
		{
			commands_list = commands_list->next;
			i++;
		}
	}
	else
		commands_list = commands_list->next;
	return (commands_list);
}
