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
# include <termios.h>
# include "../libft/libft.h"

# define EXIT_SUCCESS 0
# define EXIT_FAILURE 1
# define EXIT_CMD_NOT_FOUND 127

extern int g_blocking_command;

typedef struct s_env
{
	char	*name;
	char	*value;
}	t_env;

typedef struct s_command
{
	char		*cmd;
	int			num_args;
	char		**args;
	char		*operator;
	char		*outfile_redirect;
	char		*infile_redirect;
	char		*infile;
	char		*outfile;
	t_list		*env;
	int			exit_code;
}	t_command;

typedef enum e_token_type
{
	WORD = 0,
	PIPE = 1,
	REDIRECTION = 2,
	EMPTY = 3,
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*content;
	t_list			*env;
}	t_token;

// Init structs
t_token		*create_token(char *str, int type, t_list *env);
t_command	*create_command(int num_args, t_list *env, int exit_code);
t_env		*create_env_var(char *name, char *value);

// Parser
t_list		*parser(t_list *tokens_list, t_list *env, int exit_code);
bool		is_file(char *path_cmd);
int			ft_num_args(t_list *tokens_list);
t_token		*update_tokens_list(t_list **tokens_list, t_token *token);

// Lexer
t_list		*lexer(char *cmd, t_list *env);
int			check_for_word_in_single_quotes(char *cmd, int i,
				t_list **tokens_list, t_list *env);
int			check_for_word_in_double_quotes(char *cmd, int i,
				t_list **tokens_list, t_list *env);
int			check_for_word_without_quotes(char *cmd, int i,
				t_list **tokens_list, t_list *env);
int			check_for_outfile_redirection(char *cmd, int i,
				t_list **tokens_list, t_list *env);
int			check_for_infile_redirection(char *cmd, int i,
				t_list **tokens_list, t_list *env);
int			check_for_redirections(char *cmd, int i,
				t_list **tokens_list, t_list *env);

// Executor
int			executor(t_list *commands_list);
int			execute(t_command *command);
void		execute_cmd(t_command *command, char **argv, char *envp[2]);
int			wait_processes(int num_pipes, pid_t *pids);
t_list		*update_commands_list(t_list *commands_list, int num_pipes);
void		child_process(t_command *command, int *pipe_fd);
bool		is_builtin(char *cmd);
int			execute_builtin_parent(t_command *command, int *pipe_fd);
int			execute_builtin_child(t_command *command, int *pipe_fd);
void		free_argv(char **argv);

// Pipes
int			**initialize_pipe_fds(int num_pipes);
int			create_pipes(int num_pipes, int **pipe_fd);
int			get_num_pipes(t_list *commands_list);
int			ft_pipe(t_list *commands_list, int num_pipes);

// Fds
void		set_up_fds(int **pipe_fd, int num_pipes, int i);
void		free_pipe_fds(int **pipe_fd, int num_pipes);
void		close_fds(int num_pipes, int **pipe_fd);

// Redirections
void		redirect_output(t_command *command);
void		redirect_input(t_command *command);

// Builtins
int			ft_echo(t_command *command);
int			ft_cd(t_command *command);
int			ft_pwd(void);
int			ft_env(t_command *command, char *cmd);
int			ft_export(t_command *command);
int			ft_unset(t_command *command);
int			clear(void);
bool		is_env_var(t_list *env_list, char *var_name);
char		*ft_getenv(t_list *env_list, char *var_name);

// Signals
void		sigint_handler(int signum);
void		sigquit_handler(int signum);

// Utils
int			return_with_error(char *error_msg);
void		print_token(void *content);
void		print_command(void *content);
bool		is_file(char *path_cmd);
bool		is_same_string(char *op1, char *op2);
bool		is_infile_redirection(char *cmd);
bool		is_pipe(char *cmd);
bool		is_outfile_redirection(char *cmd);
bool		is_valid_identifier(char *str);

// Free data
void		free_tokens(t_list *tokens_list);
// void		free_env(t_env *env);
void		free_commands(t_list *commands_list);

#endif