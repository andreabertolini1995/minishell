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
# include <fcntl.h>
# include <signal.h>
# include "libft/libft.h"

extern int g_exit_code;

typedef struct s_env
{
    char **envp;
}   t_env;

typedef struct s_command
{
    char                *cmd;
    int                 num_args;
    char                **args;
    char                *operator;
    char                *redirection;
    char                *infile;
    char                *outfile;
    t_env               *env;
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
t_list      *parser(t_list *tokens_list, t_env *env);
bool        is_file(char *path_cmd);

// Lexer
t_list      *lexer(char *cmd);

// Executor
void        executor(t_list *commands_list);
int         execute(t_command *command);
int         **initialize_pipe_fds(int num_pipes);
int         create_pipes(int num_pipes, int **pipe_fd);
int         get_num_pipes(t_list *commands_list);
int         ft_pipe(t_list *commands_list, int num_pipes);
void        close_fds(int num_pipes, int **pipe_fd);
void        wait_processes(int num_pipes, int *pids);

// Redirections
void        redirect_output(t_command *command);
void        redirect_input(t_command *command);
bool        is_same_string(char *op1, char *op2);

// Builtins
void        ft_echo(t_command *command);
void        ft_cd(t_command *command);
void        ft_pwd();
void        ft_env(t_command *command);
void        *ft_export(t_command *command);
void        *ft_unset(t_command *command);
void        clear();

// Error handling
int         return_with_error(char *error_msg);

// Prints
void        print_token(void *content);
void        print_command(void *content);

// Signals

#endif