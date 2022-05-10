/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 12:51:06 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/10 13:23:47 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	executor(t_data *data)
{
	t_parser *cmd_table;

	cmd_table = data->parser;
	while (cmd_table)
	{
		find_command(data, *cmd_table->command, cmd_table->command);
		cmd_table = cmd_table->next;
	}
}

void	find_command(t_data *data, char *command, char **cmd_table)
{
	if (!ft_strncmp(command, "env", 4))
		ft_env(data->env);
	else if (!ft_strncmp(command, "exit", 5))
		ft_exit();
	else if (!ft_strncmp(command, "pwd", 4))
		ft_pwd();
	else if (!ft_strncmp(command, "cd", 3))
		ft_cd(cmd_table);
	else if (!ft_strncmp(command, "echo", 5))
		ft_echo(cmd_table);
}