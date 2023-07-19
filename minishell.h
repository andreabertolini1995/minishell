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

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

// Command struct
typedef struct s_command
{
    char                *cmd;
    char                *arg;
    char                *operator;
    struct s_command    *next;
}   t_command;

// Parser
t_command   *parser(char **tokens);

// Path
char	    *combine_path_cmd(char *cmd);

// List utils
void	    add_cmd_back(t_command **lst, t_command *new);
t_command	*last_cmd(t_command *lst);

// Pipex
char	*combine_path_cmd(char *cmd);

// Utils
char        *ft_strcat(char *dest, char *src);
char	    *ft_strncpy(char *dest, char *src, unsigned int n);

#endif