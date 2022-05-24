/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/16 12:03:21 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/24 11:04:12 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	varname_len(char *var)
{
	int i;
	
	i = 0;
	while (var[i] && ft_isalnum(var[i]))
		i++;
	return (i);
}

void	export_check_dup(char ***env, char *command)
{
	int i;

	i = 0;
	while (env[0][i])
	{
		if (!ft_strncmp(command, env[0][i], varname_len(env[0][i])))
		{
			remove_line_from_env(env, command);
			return ;
		}
		i++;
	}
	return ;
}

void	remove_line_from_env(char ***env, char *var)
{
	int i;
	int j;
	int oui;
	char **new_env;

	i = 0;
	j = 0;
	oui = 0;
	new_env = safe_calloc(dp_len(*env), sizeof(char *));
	while (env[0][i])
	{
		if (ft_strncmp(env[0][i], var, varname_len(env[0][i])))
			new_env[j++] = ft_strdup(env[0][i]);
		else
			oui++;
		i++;
	}
	free_dp(*env);
	*env = new_env;
}

void	add_line_to_env(char ***env, char *new_var)
{
	int		len;	
	char	**new_env;

	len = dp_len(*env);
	new_env = env_dup(*env, len + 2);
	new_env[len] = ft_strdup(new_var);
	free_dp(*env);
	*env = new_env;
}

int	export_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		a;

	i = 0;
	a = 0;
	if (!n)
		return (-260);
	if (s1[i] == '\0' && s2[i] == '\0')
		return ((unsigned char)s1[i] - s2[i]);
	while (s1[i] != '\0' && i != n)
	{	
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - s2[i]);
		i++;
	}
	if (s2[i] != '\0' && i != n)
		return ((unsigned char)s1[i] - s2[i]);
	return (a);
}
