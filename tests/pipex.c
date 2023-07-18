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

/* Example of implement a pipe as in the pipex project.
    Only handling two processes for the moment. */

int ft_pipe(char *cmd1, char *cmd2)
{
    int pipe_fd[2];
    int id;

    if (pipe(pipe_fd) == -1)
        return (1);
    id = fork();
    if (id == -1)
        return (2);
    if (id == 0)
    {
        close(pipe_fd[0]);
        dup2(pipe_fd[1], STDOUT_FILENO);
        close(pipe_fd[1]);
    }
    else
    {
        close(pipe_fd[1]);
        dup2(pipe_fd[0], STDIN_FILENO);
        close(pipe_fd[0]);
        //wait(NULL);
    }
    return (0);
}

int main(int argc, char **argv)
{
    ft_pipe(argv[1], argv[2]);
}
