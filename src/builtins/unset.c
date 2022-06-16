/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:43:36 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/10 14:45:59 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char ***env, char **cmd_table)
{
	if (!cmd_table)
		return ;
	while (*cmd_table && (ft_isalpha(*cmd_table[0]) || \
		*cmd_table[0] == '_'))
	{
		remove_line_from_env(env, *cmd_table);
		cmd_table++;
	}
	if (*cmd_table && !ft_isalpha(*cmd_table[0]))
		printf("minishell: unset: %s: not a valid identifier\n", *cmd_table);
	g_exit_code = 1;
}
