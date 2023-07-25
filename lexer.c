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

static t_token *create_token(char *str, int type)
{
    t_token *token;

    token = (t_token *) malloc (sizeof(t_token));
    if (token == NULL)
        return (NULL);
    token->content = str;
    token->type = type;
    return (token);
}

static int    check_for_operators(char *cmd, int i, t_list **tokens_list)
{
    if (cmd[i] == '|')
    {
        ft_lstadd_back(tokens_list, ft_lstnew(create_token("|", PIPE)));
        i++;
    }
    else if (cmd[i] == '>')
    {
        if (cmd[i + 1] == '>')
        {
            ft_lstadd_back(tokens_list, ft_lstnew(create_token(">>", R_D_RDIR)));
            i++;
        }
        else
            ft_lstadd_back(tokens_list, ft_lstnew(create_token(">", R_S_RDIR)));
        i++;
    }  
    else if (cmd[i] == '<')
    {
        if (cmd[i + 1] == '<')
        {
            ft_lstadd_back(tokens_list, ft_lstnew(create_token("<<", L_D_RDIR)));
            i++;
        }
        else
            ft_lstadd_back(tokens_list, ft_lstnew(create_token("<", L_S_RDIR)));
        i++;
    }
    return (i);
}

static char *create_word(char *cmd, int length, int i)
{
    char    *word;
    int     j;

    word = (char*) malloc (sizeof(char) * length);
    if (word == NULL)
        return (NULL);
    j = 0;
    while (length > 0)
    {
        word[j] = cmd[i - length];
        length--;
        j++;
    }
    word[j] = '\0';
    return (word);
}

static char *check_if_env(char *word)
{   
    
    if(word[0] == '$' && word[1])
    {
        word += 1;    
        return(getenv(word));
    }
    return(word);
}

t_list  *lexer(char *cmd)
{
    size_t  i;
    int     length;
    char    *word;
    t_list  *tokens_list;

    i = 0;
    tokens_list = NULL;
    while (cmd[i] != '\0')
    {
        i = check_for_operators(cmd, i, &tokens_list);
        length = 0;
        // if case for "" and ' look for the 2nd parenthesis, if 2 are there, dont include them in the WORD.
        // but include operators like "|" as chars.For " -> $ specifications. if there is only one bash calls some quote shit, where u can right in.
        // (maybe) if (cmd[i] " or ')  while (cmd[i]!= ' or "){ length++;i++} call word_create(cmd, length, i); what to do when only open parenthesis without closing?
        while (cmd[i] != '|' && cmd[i] != '>' && cmd[i] != '<'
            && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '\0')
        {
            length++;
            i++;
        }
        if (length > 0)
        {
            word = create_word(cmd, length, i);
            word = check_if_env(word);
            ft_lstadd_back(&tokens_list, ft_lstnew(create_token(word, WORD)));
        }
        while (cmd[i] == ' ' || cmd[i] == '\t')
            i++;
    }
    return (tokens_list);
}
