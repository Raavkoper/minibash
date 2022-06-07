/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:37:31 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/07 11:33:13 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(char **cmd_table)
{
	if (!*cmd_table)
	{
		printf("\n");
		return ;
	}
	if (!check_add_n(*cmd_table) && ft_strncmp(*cmd_table, "-n", 3))
		return (print_echo(cmd_table, 1));
	while (*cmd_table && (check_add_n(*cmd_table) || \
		!ft_strncmp(*cmd_table, "-n", 3)))
		cmd_table++;
	if (*cmd_table)
		return (print_echo(cmd_table, 0));
}

void	print_echo(char **cmd_table, int nl)
{
	while (*cmd_table)
	{
		if (*cmd_table[0] == '~')
		{
			if (check_add_chars(*cmd_table))
			{
				printf("%s", getenv("HOME"));
				if (check_add_chars(*cmd_table) == 2)
					printf("%s", &cmd_table[0][1]);
				cmd_table++;
				if (*cmd_table)
					printf(" ");
				continue ;
			}
		}
		printf("%s", *cmd_table);
		cmd_table++;
		if (*cmd_table)
			printf(" ");
	}
	if (nl)
		printf("\n");
}

int	check_add_n(char *str)
{
	if (str[0] == '-')
		str++;
	while (*str && *str == 'n')
		str++;
	if (!*str)
		return (1);
	return (0);
}

int	check_add_chars(char *str)
{
	if (!str[1])
		return (1);
	if (str[1] == '/')
		return (2);
	return (0);
}
