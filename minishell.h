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
# include <sys/wait.h>
# include "libft/libft.h"

// Command struct
typedef struct s_command
{
    char                *cmd;
    int                 num_args;
    char                **args;
    char                *operator;
    struct s_command    *next;
}   t_command;


typedef enum e_token_type
{
    WORD = 0,
    PIPE = 1,
    R_S_RDIR = 2, // right-single
    R_D_RDIR = 3, // right-double
    L_S_RDIR = 4, // left-single
    L_D_RDIR = 5, // left-double
}   t_token_type;


typedef struct s_token
{
    t_token_type    type;
    char            *content;
}   t_token;


// Parser
t_list      *parser(t_list *tokens_list);

// Lexer
t_list      *lexer(char *cmd);

// Executor
int         execute_cmd(t_command *command);

// Utils
char        *ft_strcat(char *dest, char *src);
char	    *ft_strncpy(char *dest, char *src, unsigned int n);

// Prints
void        print_token(void *content);
void        print_command(void *content);

#endif