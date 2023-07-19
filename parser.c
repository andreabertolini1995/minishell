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

// bool    is_operator(char *str)
// {
//     if (!ft_strncmp(str, "&", ft_strlen(str)) || !ft_strncmp(str, ";", ft_strlen(str))
//         || !ft_strncmp(str, "&&", ft_strlen(str)) || !ft_strncmp(str, "|", ft_strlen(str))
//         || !ft_strncmp(str, "||", ft_strlen(str)))
//         return true;
//     else
//         return false;
// }

/*  Function to create a new command struct. 
    Currently assuming the only fields are cmd, arg and operator
    and there can be only one argument. */
t_command   *new_command(char **tokens, int i)
{
    t_command   *tmp;

    tmp = (t_command*) malloc (sizeof(t_command));
    if (tmp == NULL)
        return (NULL);
    while (!ft_strncmp(tokens[i], "|", ft_strlen(tokens[i])))
    {
        if (is_cmd(tokens[i]))
            tmp->cmd = tokens[i];
        else
            tmp->arg = tokens[i];
        i++;
    }
    if (i == (sizeof(tokens)/sizeof(char*)))
        tmp->operator = NULL;
    else
        tmp->operator = tokens[i];
    tmp->next = NULL;
    return (tmp);
}

/* Function to get a list of tokens as input and organize its data into a Command Table. */
t_command *parser(char **tokens)
{
    t_command       *commands_list;
    unsigned long   i;

    commands_list = (t_command*) malloc (sizeof(t_command));
    if (commands_list == NULL)
        return (NULL);
    i = 0;
    while (i < (sizeof(tokens)/sizeof(char*)))
    {
        if (i == 0)
            commands_list = new_command(tokens, i);
        else
            add_cmd_back(&commands_list, new_command(tokens, i));
        i = i + 3; // hardcoded - to be changed
    }
    return (commands_list);
}
