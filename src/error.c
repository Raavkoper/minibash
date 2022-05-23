/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/05 10:48:53 by cdiks         #+#    #+#                 */
/*   Updated: 2022/05/23 19:31:51 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    error_check(t_lexer **lexer)
{
    check_token(lexer);
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