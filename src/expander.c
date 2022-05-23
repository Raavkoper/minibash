/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 12:34:39 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/23 12:38:32 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_expansion(char **env, char *var)
{
	// int i;
	// int len;

	// if (!isdollar(var) || isquote(var))
	// 	return (1);
	// i = 1;
	// len = varname_len(var) - 1;
	// if (ft_isdigit(var[1]) && var[2])
	// 	return (1);
	// while (*env && ft_strncmp(*env, &var[1], len))
	// 	env++;
	// if (*env && !ft_strncmp(*env, &var[1], len))
	// 	return (1);
	return (1);
}

char	*expander(char **env, char *var)
{
	int i;
	char *ret;

	i = 0;
	ret = "";
	while (var[i])
	{
		if (var[i] == '$' && ft_isdigit(var[i + 1]))
			ret = ft_strjoin(ret, dub_min_digit(&var[i + 2], &i));
		if (var[i] == '$' && var[i + 1])
			ret = ft_strjoin(ret, cpy_env_var(env, &var[i + 1], &i));
		else
		{
			ret = add_char(ret, var[i]);
			i++;
		}
	}
	return (ret);
}


char	*cpy_env_var(char **env, char *var, int *x)
{
	int len;
	int env_len;
	int i;

	i = 0;
	len = varname_len(var);
	while (env[i])
	{
		env_len = varname_len(env[i]);
		if (env_len == len)
		{
			if (!ft_strncmp(env[i], var, env_len))
			{
				*x += len + 1;
				return (ft_strdup(&env[i][len + 1]));
			}
		}
		i++;
	}
	*x += len + 1;
	return ("");
}
// char	*expander(char **env, char *var)
// {
// 	int i;
// 	int len;
// 	char *ret;

// 	i = 0;
// 	len = varname_len(var) - 1;
// 	ret = "";
// 	if (ft_isdigit(var[1]) && var[2])
// 		return (ft_strdup(&var[2]));
// 	// if (var[0] == '"')
// 	// 	var = trim_double(var, 1);
// 	if (isquote(var))
// 		return (trim_qoutes(var));
// 	while (env[i])
// 	{
// 		if (varname_len(env[i]) == len)
// 		{
// 			if (!ft_strncmp(env[i], &var[1], len))
// 				ret = ft_strjoin(ret, (ft_strdup(&env[i][len + 1])));
// 		}
// 		i++;
// 	}
// 	ret = ft_strjoin(ret, check_add_string(&var[len + 1]));
// 	if (!ret[0])
// 		ret = NULL;
// 	return (ret);
// }

char	*trim_qoutes(char *word)
{
	int quote;
	int count;
	char *ret;
	int i;
	
	ret = ft_calloc(ft_strlen(word), sizeof(char));
	if (!ret)
		exit(1);
	count = 0;
	i = 0;
	quote = 0;
	while (*word)
	{
		if ((*word == SINGLE_QUOTE || *word == DOUBLE_QUOTE) && (*word == quote || count == 0))
		{
			quote = *word;
			word++;
			count++;
			count %= 2;
			continue;
		}
		ret[i] = *word;
		i++;
		word++;
	}
	return (ret);
}
