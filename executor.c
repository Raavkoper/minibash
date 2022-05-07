/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 12:51:06 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/07 13:56:23 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	executor(t_data *data)
{
	t_parser *cmd_table;

	cmd_table = data->parser;
	while (cmd_table)
	{
		find_command(data, *cmd_table->command);
		cmd_table = cmd_table->next;
	}
}

void	find_command(t_data *data, char *command)
{
	if (!ft_strncmp(command, "env", 3))
		ft_env(data->env);
	if (!ft_strncmp(command, "exit", 4))
		ft_exit();
}