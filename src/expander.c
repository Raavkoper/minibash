/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 12:34:39 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/19 14:46:37 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_expansion(char **env, char *var)
{
	int i;
	int len;

	if (var[0] != '$')
		return (1);
	i = 1;
	len = varname_len(var) - 1;
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
	len = varname_len(var);
	while (env[i])
	{
		if (!ft_strncmp(env[i], &var[1], varname_len(env[i])))
			return (ft_strdup(&env[i][len]));
		i++;
	}
	return (NULL);
}