/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:13:34 by rkoper            #+#    #+#             */
/*   Updated: 2022/04/26 15:59:51 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

int main(int argc, char **argv)
{
	t_data data;

	if (argc == 2)
		lexer(&data, argv[1]);
	print_lexer(data.lexer);
	while (1)
		init_shell();
	return (0);
}