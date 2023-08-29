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

static int	ft_num_args(t_list *tokens_list)
{
	int		num_args;
	t_token	*token;
	int		list_size;

	list_size = ft_lstsize(tokens_list);
	num_args = 0;
	token = tokens_list->content;
    if (token->type != WORD)
        return (0); // hardcoded for << 
	while ((token->type == WORD || token->type == SPACE) && tokens_list != NULL)
	{
		num_args++;
		tokens_list = tokens_list->next;
		if (tokens_list != NULL)
			token = tokens_list->content;
	}
	if (list_size == 1)
		return (num_args - 1);
	else
		return (num_args - 2); // skipping the space after the operator
}

static void	add_redirection(t_command *command,
			t_token *token, t_list **tokens_list, char *str)
{
	t_token	*next_token;

    if (is_same_string(str, "infile"))
    {
        command->infile_redirect = token->content;
        next_token = (*tokens_list)->next->content;
        command->infile = ft_strdup(next_token->content);
    }
    else
    {
        command->outfile_redirect = token->content;
        next_token = (*tokens_list)->next->content;
        command->outfile = ft_strdup(next_token->content);
    }
    *tokens_list = (*tokens_list)->next->next;
}

static void	parse_cmd_args(t_command *command,
			t_list **tokens_list, t_token **token)
{
	int	arg_index;
	int	list_size;

	arg_index = 0;
	list_size = ft_lstsize((*tokens_list));
	if (list_size > 1)
		(*tokens_list) = (*tokens_list)->next; // skipping the first space
	while (((*token)->type == WORD || (*token)->type == SPACE) && (*tokens_list) != NULL)
	{
		if (command->cmd == NULL)
		{
			if ((*token)->content == NULL) // in case $(not-env-variable)
				command->cmd = NULL;
			else
				command->cmd = ft_strdup((*token)->content);
		}
		else
		{
			command->args[arg_index] = ft_strdup((*token)->content);
			arg_index++;
		}
		(*tokens_list) = (*tokens_list)->next;
		if ((*tokens_list) != NULL)
			(*token) = (*tokens_list)->content;
	}
}

static void	parse_redirections_pipes(t_command *command,
			t_list **tokens_list, t_token **token)
{
	if (tokens_list != NULL && (*token)->content != NULL)
	{
		if (is_infile_redirection((*token)->content))
			add_redirection(command, *token, tokens_list, "infile");
		if ((*tokens_list) != NULL)
		{
			(*token) = (*tokens_list)->content;
			if (is_outfile_redirection((*token)->content))
				add_redirection(command, *token, tokens_list, "outfile");
			if ((*tokens_list) != NULL)
			{
				(*token) = (*tokens_list)->content;
				if (is_pipe((*token)->content))
					command->operator = ft_strdup((*token)->content);
			}
			if ((*tokens_list) != NULL)
				(*tokens_list) = (*tokens_list)->next;
		}
	}
}

t_list	*parser(t_list *tokens_list, t_list *env)
{
	t_list		*commands_list;
	t_token		*token;
	t_command	*command;
	int			num_args;

	commands_list = NULL;
	while (tokens_list != NULL)
	{
		token = tokens_list->content;
		num_args = ft_num_args(tokens_list);
		command = create_command(num_args, env);
		parse_cmd_args(command, &tokens_list, &token);
		parse_redirections_pipes(command, &tokens_list, &token);
		ft_lstadd_back(&commands_list, ft_lstnew(command));
	}
	return (commands_list);
}
