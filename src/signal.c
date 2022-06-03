/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 10:32:21 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/03 14:48:00 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(void)
{
	// signal(SIGINT, new_prompt);
}

void	new_prompt(int sig)
{
	ft_putstr_fd("\n", 1);
	// rl_replace_line(0);
	rl_redisplay();
}
