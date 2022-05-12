/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 10:32:21 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/12 12:03:24 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(void)
{
	// signal(SIGINT, new_prompt);
}

void	new_prompt(int sig)
{
	// ft_putstr_fd("\b\b  ", 2);
	ft_putstr_fd("\n", 1);
	ft_putstr_fd("\033[1m\033[32mminishell$> \x1B[0m", 1);
}