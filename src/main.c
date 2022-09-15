/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 14:13:34 by rkoper        #+#    #+#                 */
/*   Updated: 2022/09/15 13:26:28 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	data = (t_data){0, 0, 0, 0, 0};
	data.env = env_dup(env, dp_len(env) + 1);
	if (argc != 1)
	{
		write(2, "\x1B[31mNot in the mood for arguments rn (ง'̀-'́)ง\x1B[0m\n", 58);
		exit(1);
	}
	run_shell(&data);
	argv = NULL;
	return (0);
}
