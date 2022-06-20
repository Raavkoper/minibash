/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 14:13:34 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/20 11:53:33 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data = (t_data){0, 0, 0, 0};
	data.env = env_dup(env, dp_len(env) + 1);
	if (argc != 1)
	{
		write(2, "invalid amount of arguments given... Usage:./minishell\n", 56);
		exit(1);
	}
	run_shell(&data);
	argv = NULL;
	return (0);
}
