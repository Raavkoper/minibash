/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:39:26 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/10 13:40:06 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**get_env(char **env)
{
	return NULL;
}

void	ft_env(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;	
	}
}
