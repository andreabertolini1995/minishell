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

bool    is_file(char *path_cmd)
{
    if (access(path_cmd, F_OK) == 0)
        return true;
    else
        return false;
}

static bool    is_pipe_or_redirect(char *str)
{
    if (!ft_strncmp(str, ">", ft_strlen(str))
        || !ft_strncmp(str, "<", ft_strlen(str))
        || !ft_strncmp(str, ">>", ft_strlen(str))
        || !ft_strncmp(str, "<<", ft_strlen(str))
        || !ft_strncmp(str, "|", ft_strlen(str)))
        return true;
    else
        return false;
}

static t_command *create_command(int num_args)
{
    t_command *command;

    command = (t_command *) malloc (sizeof(t_command));
    if (command == NULL)
        return (NULL);
    command->cmd = NULL;
    command->num_args = num_args;
    command->args = (char**) malloc (sizeof(char*) * num_args);
    if (command->args == NULL)
        return (NULL);
    command->operator = NULL;
    command->infile = NULL;
    command->outfile = NULL;
    return (command);
}

static int ft_num_args(t_list *tokens_list)
{
    int     num_args;
    t_token *token;

    num_args = 0;
    token = tokens_list->content;
    while (token->type == WORD && tokens_list != NULL)
    {
        num_args++;
        tokens_list = tokens_list->next;
        if (tokens_list != NULL)
            token = tokens_list->content;
    }
    return (num_args - 1);
}

t_list  *parser(t_list *tokens_list)
{
    t_list          *commands_list;
    t_token         *token;
    t_token         *next_token;
    t_command       *command;
    int             num_args;
    int             arg_index;

    commands_list = NULL;
    while (tokens_list != NULL)
    {
        token = tokens_list->content;
        num_args = ft_num_args(tokens_list);
        command = create_command(num_args);
        arg_index = 0;
        while (token->type == WORD && tokens_list != NULL)
        {
            if (command->cmd == NULL)
                command->cmd = token->content;
            else
            {
                command->args[arg_index] = token->content;
                arg_index++;
            }  
            tokens_list = tokens_list->next;
            if (tokens_list != NULL)
                token = tokens_list->content;
        }
        if (is_pipe_or_redirect(token->content))
        {
            if (is_same_string(token->content, "<")
                || is_same_string(token->content, "<<"))
            {
                next_token = tokens_list->next->content;
                command->infile = next_token->content;
                tokens_list = tokens_list->next;
            }
            command->operator = token->content;
            tokens_list = tokens_list->next;
        }
        ft_lstadd_back(&commands_list, ft_lstnew(command));
    }
    return (commands_list);
}
