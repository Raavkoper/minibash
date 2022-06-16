/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:40:15 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/16 14:18:18 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(char **cmd_table)
{
	char	*command;
	int		exitcode;

	printf("%sFine go talk to your other shell😒%s\n", RED, NC);
	command = NULL;
	exitcode = 0;
	if (cmd_table[0])
		command = ft_strdup(cmd_table[0]);
	if (command)
	{
		if (is_wholenum(command))
		{
			if (cmd_table[1])
			{
				printf("minishell: exit: muchos argumentos\n");
				free(command);
				g_exit_code = 1;
				return ;
			}
			exitcode = ft_atoi(command);
		}
		else
		{
			printf("minishell: exit: %s: numeric argument required\n", command);
			exitcode = 255;
		}
		free(command);
	}
	exit(exitcode);
}
