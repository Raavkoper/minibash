/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:13:34 by rkoper            #+#    #+#             */
/*   Updated: 2022/05/05 11:09:40 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int argc, char **argv, char **env)
{
	t_data data;
	
	// while (*env)
	// {
	// 	printf("%s\n", *env);
	// 	env++;
	// }	
	if (argc != 1)
	{
		printf("invalid amount of arguments given... Usage:./minishell\n");
		exit(1);
	}
	run_shell(&data);
	return (0);
}