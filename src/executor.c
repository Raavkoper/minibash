/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 12:51:06 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/10 11:37:46 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_data *data)
{
	t_parser	*cmd_table;

	if (!data->parser)
		return ;
	cmd_table = data->parser;
	while (cmd_table)
	{
		if (!find_command(data, *cmd_table->command, cmd_table->command))
			return ;
		cmd_table = cmd_table->next;
	}
}

int	find_command(t_data *data, char *command, char **cmd_table)
{
	if (!command)
		return (0);
	if (!ft_strncmp(command, "env", 4))
		ft_env(data->env);
	else if (!ft_strncmp(command, "exit", 5))
		ft_exit(++cmd_table);
	else if (!ft_strncmp(command, "pwd", 4))
		ft_pwd(1);
	else if (!ft_strncmp(command, "cd", 3))
		ft_cd(&data->env, ++cmd_table);
	else if (!ft_strncmp(command, "echo", 5))
		ft_echo(++cmd_table);
	else if (!ft_strncmp(command, "export", 7))
		ft_export(&data->env, ++cmd_table);
	else if (!ft_strncmp(command, "unset", 6))
		ft_unset(&data->env, ++cmd_table);
	else
		return (0);
	return (1);
}
