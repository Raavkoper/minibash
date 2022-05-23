/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/16 12:03:21 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/23 12:43:40 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	varname_len(char *var)
{
	int i;
	
	i = 0;
	while (var[i] && var[i] != '=' && var[i] != '$' && var[i] != ':' && var[i] != '*' && var[i] != '"' && var[i] != '\'')
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
	new_env = ft_calloc(dp_len(*env), sizeof(char *));
	if (!new_env)
		exit(1);
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