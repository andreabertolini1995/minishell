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

bool    is_token(char *token1, char *token2)
{
    if (!ft_strncmp(token1, token2, ft_strlen(token1)))
        return (true);
    else
        return (false);
}

char *get_name_outfile(t_list *commands_list)
{
    t_command   *command;
    t_command   *next_command;

    while (commands_list != NULL)
    {
        command = commands_list->content;
        if (command->operator != NULL)
        {
            // Assuming there is only one single or double redirection at the end 
            if (is_token(command->operator, ">")
                || is_token(command->operator, ">>"))
            {
                next_command = commands_list->next->content;
                return (next_command->cmd);
            }
        }
        commands_list = commands_list->next;
    }
    return (NULL);
}

char *get_name_infile(t_list *commands_list)
{
    t_command   *command;
    t_command   *next_command;

    while (commands_list != NULL)
    {
        command = commands_list->content;
        if (command->operator != NULL)
        {
            // Assuming there is only one single or double redirection at the beginning 
            if (is_token(command->operator, "<")
                || is_token(command->operator, "<<"))
            {
                next_command = commands_list->next->content;
                return (next_command->cmd);
            }
        }
        commands_list = commands_list->next;
    }
    return (NULL);
}

void    redirect_output(t_command *command)
{
    int file;
    int file2;
    
    if (is_token(command->operator, ">"))
        file = open(command->outfile, O_WRONLY | O_CREAT, 0777);
    else
        file = open(command->outfile, O_WRONLY | O_CREAT | O_APPEND, 0777);
    file2 = dup2(file, STDOUT_FILENO);
    close(file);
}

static void    infile_redirect(char *file_name)
{
    int file;
    int file2;

    file = open(file_name, O_RDONLY);
    file2 = dup2(file, STDIN_FILENO);
    close(file);
}

void    redirect_input(t_command *command)
{
    int     file;
    char    *line;
    
    if (is_token(command->operator, "<"))
        infile_redirect(command->infile);
    else
    {
        file = open(command->infile, O_WRONLY | O_CREAT | O_APPEND, 0777);
        while (42)
        {
            line = readline("> ");
            if (strncmp(line, command->infile, ft_strlen(line)))
            {
                write(file, line, ft_strlen(line));
                write(file, "\n", 1);
            }
            else
            {
                infile_redirect(command->infile);
                unlink(command->infile);
                break;
            }
        }
    }
}
