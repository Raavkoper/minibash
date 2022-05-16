/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:37:31 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/12 10:19:02 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_echo(char **cmd_table)
{
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
				if (check_add_chars(*cmd_table) == 1)
				{
					printf("%s", getenv("HOME"));
					cmd_table++;
					if (*cmd_table)
						printf(" ");
					continue ;
				}
				if (check_add_chars(*cmd_table) == 2)
				{
					printf("%s", getenv("HOME"));
					putstr_echo(*cmd_table, 1);
					cmd_table++;
					if (*cmd_table)
						printf(" ");
					continue ;
				}
			}
			putstr_echo(*cmd_table, 0);
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
				if (check_add_chars(*cmd_table) == 1)
				{
					printf("%s", getenv("HOME"));
					cmd_table++;
					if (*cmd_table)
						printf(" ");
					continue ;
				}
				if (check_add_chars(*cmd_table) == 2)
				{
					printf("%s", getenv("HOME"));
					putstr_echo(*cmd_table, 1);
					cmd_table++;
					if (*cmd_table)
						printf(" ");
					continue ;
				}
			}
			putstr_echo(*cmd_table, 0);
			cmd_table++;
			if (*cmd_table)
				printf(" ");
		}
	}
}

void	putstr_echo(char *word, int index)
{
	int quote;
	int count;
	
	count = 0;
	while (index--)
		word++;
	while (*word)
	{
		if ((*word == SINGLE_QUOTE || *word == DOUBLE_QUOTE) && (*word == quote || count == 0))
		{
			quote = *word;
			word++;
			count++;
			count %= 2;
			continue;
		}	
		printf("%c", *word);
		word++;
	}
}

int	check_add_chars(char *str)
{
	if (!str[1])
		return (1);
	if (str[1] == '/')
		return (2);
	return (0);
}
