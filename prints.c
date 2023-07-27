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

void    print_token(void *content)
{
    t_token *token;

    token = (t_token*) content;
    printf("Content: %s\n", token->content);
    printf("Type: %d\n", token->type);
    printf("\n");
}

void    print_command(void *content)
{
    t_command   *command;
    int         i;

    command = (t_command*) content;
    printf("Command: %s\n", command->cmd);
    i = 0;
    while (i < command->num_args)
    {
        printf("Arg %d: %s\n", i + 1, command->args[i]);
        i++;
    }
    printf("Operator: %s\n", command->operator);
    printf("Infile: %s\n", command->infile);
    printf("Outfile: %s\n", command->outfile);
    printf("\n");
}
