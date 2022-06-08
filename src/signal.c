/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   signal.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/09 10:32:21 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/08 11:24:09 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signals(void)
{
	signal(SIGINT, new_prompt);
	signal(SIGQUIT, SIG_IGN);
}

void	new_prompt(int sig)
{
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
