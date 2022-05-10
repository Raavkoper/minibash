/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:37:31 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/10 13:41:48 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char **cmd_table)
{
	cmd_table++;
	if (!*cmd_table)
	{
		printf("\n");
		return ;
	}
	if (ft_strncmp(*cmd_table, "-n", 3))
	{
		while (*cmd_table)
		{
			if (*cmd_table[0] == '~')
			{
				if (check_add_chars(*cmd_table))
				{
					find_home_dir('p');
					cmd_table++;
					if (*cmd_table)
						printf(" ");
					continue ;
				}
			}
			putstr_echo(*cmd_table);
			printf(" ");
			cmd_table++;
		}
		printf("\n");
		return ;
	}
	if (!ft_strncmp(*cmd_table, "-n", 3))
	{
		cmd_table++;
		while (*cmd_table)
		{
			if (*cmd_table[0] == '~')
			{
				if (check_add_chars(*cmd_table))
				{
					find_home_dir('p');
					cmd_table++;
					if (*cmd_table)
						printf(" ");
					continue ;
				}
			}
			putstr_echo(*cmd_table);
			cmd_table++;
			if (*cmd_table)
				printf(" ");
		}
	}
}

void	putstr_echo(char *word)
{
	while (*word)
	{
		if (*word != SINGLE_QUOTE && *word != DOUBLE_QUOTE)
			printf("%c", *word);
		word++;
	}
}

int	check_add_chars(char *str)
{
	return (str[0] == '~' && !str[1]);
}
