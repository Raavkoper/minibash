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

int		dp_len(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;	
	return (i);
}

char	**get_env(char **env)
{
	int i;
	char **new_env;

	i = 0;
	new_env = ft_calloc(dp_len(env) + 1, sizeof(char *));
	if (!new_env)
		exit(1);
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
