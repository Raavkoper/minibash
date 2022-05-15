/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:43:47 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/12 13:00:05 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_export(char	**env, char **cmd_table)
{
	if (!*cmd_table)
	{
		while (*env)
		{
			printf("declare -x %s\n", *env);
			env++;
		}
		return ;
	}
}