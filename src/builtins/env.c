/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:39:26 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/23 19:36:30 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		dp_len(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;	
	return (i);
}

char	**env_dup(char **env, int size)
{
	int i;
	char **new_env;

	i = 0;
	new_env = safe_calloc(size, sizeof(char *));
	while (env[i])
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	return (new_env);
}

void	ft_env(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}
