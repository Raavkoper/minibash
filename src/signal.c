/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 10:32:21 by rkoper            #+#    #+#             */
/*   Updated: 2022/05/27 11:49:44 by cdiks            ###   ########.fr       */
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
	ft_putstr_fd("\033[1m\033[32mminishell$> \x1B[0m", 1);
}