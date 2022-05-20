/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 12:34:39 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/20 15:54:10 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_expansion(char **env, char *var)
{
	int i;
	int len;

	if (var[0] != '$' || isquote(var))
		return (1);
	i = 1;
	len = varname_len(var) - 1;
	if (ft_isdigit(var[1]) && var[2])
		return (1);
	while (*env && ft_strncmp(*env, &var[1], len))
		env++;
	if (*env && !ft_strncmp(*env, &var[1], len))
		return (1);
	return (0);
}

char	*cpy_env_var(char **env, char *var)
{
	int i;
	int len;

	i = 0;
	len = varname_len(var) - 1;
	if (ft_isdigit(var[1]) && var[2])
		return (ft_strdup(&var[2]));
	while (env[i])
	{
		if (varname_len(env[i]) == len)
		{
			if (!ft_strncmp(env[i], &var[1], len))
				return (ft_strdup(&env[i][len + 1]));
		}
		i++;
	}
	return (NULL);
}