/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eltongid <eltongid@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 21:19:57 by eltongid          #+#    #+#             */
/*   Updated: 2023/12/17 11:37:07 by eltongid         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	add_redirection(t_command *command,
			t_token *token, t_list **tokens_list, char *str)
{
	t_token	*next_token;

	if (is_same_string(str, "infile"))
	{
		command->infile_redirect = token->content;
		printf("ciao\n");
		if ((*tokens_list)->next != NULL)
		{
			printf("hey\n");
			next_token = update_tokens_list(tokens_list,
					(*tokens_list)->next->content);
			command->infile = ft_strdup(next_token->content);
		}
	}
	else
	{
		command->outfile_redirect = token->content;
		if ((*tokens_list)->next != NULL)
		{
			next_token = update_tokens_list(tokens_list,
					(*tokens_list)->next->content);
			command->outfile = ft_strdup(next_token->content);
		}
	}
	printf("hu\n");
	(*tokens_list) = (*tokens_list)->next;
	if ((*tokens_list) != NULL)
		(*tokens_list) = (*tokens_list)->next;
}

static	void	update_cmd(t_command *command, t_token *token)
{
	if (token->content == NULL)
		command->cmd = NULL;
	else
		command->cmd = ft_strdup(token->content);
}

static void	parse_cmd_args(t_command *command,
			t_list **tokens_list, t_token **token)
{
	int	arg_index;
	int	list_size;

	arg_index = 0;
	list_size = ft_lstsize((*tokens_list));
	if (list_size > 1)
		(*tokens_list) = (*tokens_list)->next;
	while (((*token)->type == WORD || (*token)->type == CONST
			|| (*token)->type == EMPTY) && (*tokens_list) != NULL)
	{
		if (command->cmd == NULL)
			update_cmd(command, (*token));
		else
		{
			if ((*token)->type == WORD || (*token)->type == CONST
				|| (is_same_string(command->cmd, "echo")))
			{
				command->args[arg_index] = ft_strdup((*token)->content);
				arg_index++;
			}
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
		if (is_infile_redirection((*token)->content)
			&& (*tokens_list) != NULL)
			add_redirection(command, *token, tokens_list, "infile");
		if ((*tokens_list) != NULL)
		{
			(*token) = (*tokens_list)->content;
			while (is_outfile_redirection((*token)->content)
				&& (*tokens_list) != NULL)
			{
				add_redirection(command, *token, tokens_list, "outfile");
				open(command->outfile, O_WRONLY | O_CREAT, 0777);
			}
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

t_list	*parser(t_list *tokens_list, t_list *env, int exit_code)
{
	t_list		*commands_list;
	t_token		*token;
	t_command	*command;
	int			num_args;

	commands_list = NULL;
	command = NULL;
	while (tokens_list != NULL)
	{
		token = update_tokens_list(&tokens_list, tokens_list->content);
		if (!is_same_string(token->content, " "))
		{
			num_args = ft_num_args(tokens_list);
			command = create_command(num_args, env, exit_code);
			parse_cmd_args(command, &tokens_list, &token);
			parse_redirections_pipes(command, &tokens_list, &token);
			ft_lstadd_back(&commands_list, ft_lstnew(command));
		}
	}
	if (command != NULL && is_blocking_command(command))
	{
		signal(SIGINT, sigint_blocking_cmd_handler);
		signal(SIGQUIT, sigquit_handler);
	}
	return (commands_list);
}
