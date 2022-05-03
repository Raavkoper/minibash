/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 14:13:34 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/03 11:15:19 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int argc, char **argv)
{
	t_data data;
	
	if (argc != 1)
	{
		printf("invalid amount of arguments given... Usage:./minishell\n");
		exit(1);
	}
	run_shell(&data);
	return (0);
}