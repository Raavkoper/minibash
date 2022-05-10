/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 14:13:34 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/10 13:45:35 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	t_data data;
	
	data.env = env;
	if (argc != 1)
	{
		printf("invalid amount of arguments given... Usage:./minishell\n");
		exit(1);
	}
	handle_signals();
	run_shell(&data);
	return (0);
}