/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   is_check.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 14:54:34 by rkoper        #+#    #+#                 */
/*   Updated: 2022/04/26 14:58:09 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int	iswhitespace(char c)
{
	return (c == 32 || c == 10 || c == 9 || c == 11);
}

int istoken(char c)
{
	return (c == 60 || c == 62 || c == 39 || c == 34 || c == 124);
}