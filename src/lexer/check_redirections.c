/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abertoli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/18 17:33:54 by abertoli          #+#    #+#             */
/*   Updated: 2023/12/16 21:22:02 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*check_for_outfile_redirection(char *cmd,
				t_list **tokens_list, t_list *env)
{
	if (*(cmd + 1) == '>')
	{
		ft_lstadd_back(tokens_list,
			ft_lstnew(create_token(">>", REDIRECTION, env)));
		cmd++;
	}
	else
		ft_lstadd_back(tokens_list,
			ft_lstnew(create_token(">", REDIRECTION, env)));
	cmd++;
	return (cmd);
}

char	*check_for_infile_redirection(char *cmd,
				t_list **tokens_list, t_list *env)
{
	if (*(cmd + 1) == '<')
	{
		ft_lstadd_back(tokens_list,
			ft_lstnew(create_token("<<", REDIRECTION, env)));
		{
			signal(SIGINT, sigint_handler_heredoc1);//initialised here
			cmd++;
		}
	}
	else
		ft_lstadd_back(tokens_list,
			ft_lstnew(create_token("<", REDIRECTION, env)));
	cmd++;
	return (cmd);
}

char	*check_for_redirections(char *cmd, t_list **tokens_list, t_list *env)
{
	if (*cmd == '>')
		cmd = check_for_outfile_redirection(cmd, tokens_list, env);
	else if (*cmd == '<')
		cmd = check_for_infile_redirection(cmd, tokens_list, env);
	return (cmd);
}
