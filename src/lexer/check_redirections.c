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

int	check_for_outfile_redirection(char *cmd, int i,
				t_list **tokens_list, t_list *env)
{
	if (cmd[i + 1] == '>')
	{
		ft_lstadd_back(tokens_list,
			ft_lstnew(create_token(">>", R_D_RDIR, env)));
		i++;
	}
	else
		ft_lstadd_back(tokens_list,
			ft_lstnew(create_token(">", R_S_RDIR, env)));
	i++;
	return (i);
}

int	check_for_infile_redirection(char *cmd, int i,
				t_list **tokens_list, t_list *env)
{
	if (cmd[i + 1] == '<')
	{
		ft_lstadd_back(tokens_list,
			ft_lstnew(create_token("<<", L_D_RDIR, env)));
		i++;
	}
	else
		ft_lstadd_back(tokens_list,
			ft_lstnew(create_token("<", L_S_RDIR, env)));
	i++;
	return (i);
}

int	check_for_redirections(char *cmd, int i,
				t_list **tokens_list, t_list *env)
{
	if (cmd[i] == '>')
		i = check_for_outfile_redirection(cmd, i, tokens_list, env);
	else if (cmd[i] == '<')
		i = check_for_infile_redirection(cmd, i, tokens_list, env);
	return (i);
}
