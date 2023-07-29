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

extern char** environ;

void    ft_echo(t_command *command)
{
    int     i;
    bool    new_line;    

    i = 0;
    if (is_token(command->args[i], "-n"))
    {
        new_line = false;
        i++;
    } 
    while (i < command->num_args)
    {
        printf("%s", command->args[i]);
        i++;
    }
    if (new_line == true)
        printf("\n");
}

void    ft_cd(t_command *command)
{
    if (is_file(command->args[0]))
        chdir(command->args[0]);
    else
        printf("minishell: cd: %s: No such file or directory\n", command->args[0]);
}

void    ft_pwd()
{
    char    buffer[1024];

    printf("%s\n", getcwd(buffer, sizeof(buffer)));
}

void    ft_env()
{
    char** env;
    
    env = environ;
    while (*env != NULL) {
        printf("%s\n", *env);
        env++;
    }
}

// void    ft_export(t_command *command)
// {
    
// }
