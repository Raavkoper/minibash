/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:40:15 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/20 09:11:08 by rkoper        ########   odam.nl         */
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
		if (ft_exit2(cmd_table, command, &exitcode))
			return ;
	}
	exit(exitcode);
}

int	ft_exit2(char **cmd_table, char *command, int *exitcode)
{
	if (is_wholenum(command))
	{
		if (cmd_table[1])
		{
			printf("minishell: exit: muchos argumentos\n");
			free(command);
			g_exit_code = 1;
			return (1);
		}
		*exitcode = ft_atoi(command);
	}
	else
	{
		printf("minishell: exit: %s: numeric argument required\n", command);
		*exitcode = 255;
	}
	free(command);
	return (0);
}
