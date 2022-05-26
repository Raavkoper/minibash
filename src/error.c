/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/05 10:48:53 by cdiks         #+#    #+#                 */
/*   Updated: 2022/05/26 11:32:00 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    error_check(t_lexer **lexer)
{
    t_lexer *iter;

	iter = *lexer;
	if (!*lexer)
		return ;
	while (iter)
	{
        if (iter->token)
        {
            if (!valid_token(iter->next, &iter->token))
            {
                print_error(lexer, iter->token);
                return ;
            }
        }
		iter = iter->next;
	}
	return ;
}

void    print_error(t_lexer **lexer, int token)
{
    if (token == 310)
        printf("minishell: syntax error near unexpected token `<<'\n");
    else if (token == 312)
	    printf("minishell: syntax error near unexpected token `>>'\n");
    else if (istoken(token))
	    printf("minishell: syntax error near unexpected token `%c'\n", (char)token);
	free_lexer(lexer);
	lexer = NULL;
}

int		valid_token(t_lexer *lexer, int *token)
{
    if (!lexer)
        return (0);
	if ((*token == '>' || *token == '|') && (!lexer->command))
        return (0);
    if ((*token == 312 || *token == 310) && (!lexer->command))
        return (0);
    if (*token == '<' && access(lexer->command, F_OK))
    {
        printf("minishell: %s: No such file or directory\n", lexer->command);
        *token = 0;
        return (0);
    }
	return (1);
}

void	*safe_calloc(size_t count, size_t size)
{
    void *ptr;

    ptr = ft_calloc(count, size);
    if (!ptr)
    {
        write(2, "failed to allocate memory\n", 27);
        exit(1);
    }
    return (ptr);
}
