/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:43:36 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/18 14:14:28 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char ***env, char **cmd_table)
{
	if (!cmd_table)
		return ;
	while (*cmd_table)
	{
		remove_line_from_env(env, *cmd_table);
		cmd_table++;
	}
}