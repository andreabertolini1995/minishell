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

extern char**   environ;
extern int      g_exit_code;

void    ft_echo(t_command *command)
{
    int     i;
    bool    new_line;    

    i = 0;
    new_line = true;
    if (is_same_string(command->args[i], "-n"))
    {
        new_line = false;
        i++;
    }
    if (is_same_string(command->args[i], "$?"))
        printf("%d\n", g_exit_code);
    while (i < command->num_args)
    {
        printf("%s", command->args[i]);
        i++;
    }
    if (new_line == true)
        printf("\n");
}

void    ft_pwd()
{
    char    buffer[1024];

    printf("%s\n", getcwd(buffer, sizeof(buffer)));
}

void    ft_env()
{
    char**  env;
    int     i;
    
    env = environ;
    i = 0;
    while (env[i] != NULL) {
        printf("%s\n", env[i]);
        i++;
    }
}
