/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   exit.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:40:15 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/10 13:49:49 by rkoper        ########   odam.nl         */
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
			exitcode = ft_atoi(command);
	}
	exit(exitcode);
}
