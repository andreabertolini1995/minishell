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

bool    is_cmd(char *str)
{
    char *path_cmd;

    path_cmd = combine_path_cmd(str);
    if (access(path_cmd, F_OK) == 0)
        return true;
    else
        return false;
}

bool    is_operator(char *str)
{
    if (str == "&" || str == ";" || str == "&&"
        || str == "|" || str == "||")
        return true;
    else
        return false;
}

/* Function to get a list of tokens as input and organize its data into a Command Table. */
t_command *parser(char **tokens)
{
    t_command   *commands_list;
    int         i;

    commands_list = (t_command*) malloc (sizeof(t_command));
    if (commands_list == NULL)
        return (NULL);
    i = 0;
    while (!is_operator(tokens[i]))
    {
        if (is_cmd(tokens[i]))
            printf("File exists.\n");
        else
            printf("File does not exist.\n");
    }
    
    
    return (commands_list);
}