/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   executor.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 12:51:06 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/09 13:10:38 by rkoper        ########   odam.nl         */
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

