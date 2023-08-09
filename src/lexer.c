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

#include "../include/minishell.h"

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
    int i;

    i = 0;
    while (word[i + 1] != '\0')
    {
        if(word[i] == '$' && word[i + 1] != '?')
        {
            word += (i + 1);
            return (getenv(word));
        }
        i++;
    }
    return (word);
}

static bool is_there_second_single_quote(char *cmd, int i)
{
    while (cmd[i] != '\0')
    {
        if (cmd[i] == '\'')
            return (true);
        i++;
    }
    return (false);
}

static bool is_there_second_double_quote(char *cmd, int i)
{
    while (cmd[i] != '\0')
    {
        if (cmd[i] == '"')
            return (true);
        i++;
    }
    return (false);
}

int   check_for_word_in_single_quotes(char *cmd, int i, t_list **tokens_list)
{
    int     length;
    char    *word;

    length = 0;
    while (cmd[i] != '\'' && cmd[i] != '\0')
    {
        length++;
        i++;
    }
    if (length > 0)
    {
        word = create_word(cmd, length, i);
        ft_lstadd_back(tokens_list, ft_lstnew(create_token(word, WORD)));
    }
    return (i);
}

int   check_for_word_in_double_quotes(char *cmd, int i, t_list **tokens_list)
{
    int     length;
    char    *tmp_word;
    char    *final_word;
    int     start;

    start = i;
    final_word = "";
    while (cmd[i] != '"' && cmd[i] != '\0')
    {
        length = 0;
        while (cmd[i] != '"' && cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '\0')
        {
            length++;
            i++;
        }
        tmp_word = create_word(cmd, length, i);
        tmp_word = check_if_env(tmp_word);
        if ((i - length) > start)
            final_word = ft_strjoin(final_word, " ");
        final_word = ft_strjoin(final_word, tmp_word);
        free(tmp_word);
        i++;     
    }
    ft_lstadd_back(tokens_list, ft_lstnew(create_token(final_word, WORD)));
    return (i);
}

int    check_for_word_without_quotes(char *cmd, int i, t_list **tokens_list)
{
    int     length;
    char    *word;

    length = 0;
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
        ft_lstadd_back(tokens_list, ft_lstnew(create_token(word, WORD)));
    }
    return (i);
}

t_list  *lexer(char *cmd)
{
    size_t  i;
    t_list  *tokens_list;

    i = 0;
    tokens_list = NULL;
    while (cmd[i] != '\0')
    {
        i = check_for_operators(cmd, i, &tokens_list);
        if (cmd[i] == '\'')
            if (is_there_second_single_quote(cmd, i))
                i = check_for_word_in_single_quotes(cmd, i + 1, &tokens_list);
            else
                i = check_for_word_without_quotes(cmd, i, &tokens_list);
        else if (cmd[i] == '"')
            if (is_there_second_double_quote(cmd, i))
                i = check_for_word_in_double_quotes(cmd, i + 1, &tokens_list);
            else
                i = check_for_word_without_quotes(cmd, i, &tokens_list);
        else
            i = check_for_word_without_quotes(cmd, i, &tokens_list);
        if (cmd[i] != '\0')
            i++;
        while (cmd[i] == ' ' || cmd[i] == '\t')
            i++;
    }
    return (tokens_list);
}
