/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 12:34:39 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/22 12:02:44 by rkoper        ########   odam.nl         */
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
	// if (var[0] == '"')
	// 	var = trim_double(var, 1);
	if (isquote(var))
		return (trim_qoutes(var, 1));
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

// char	*trim_double(char *word, int index)
// {
// 	int quote;
// 	char *ret;
// 	int i;
	
// 	ret = ft_calloc(ft_strlen(word), sizeof(char));
// 	if (!ret)
// 		exit(1);
// 	while (index--)
// 		word++;
// 	i = 0;
// 	quote = 0;
// 	while (*word)
// 	{
// 		while (*word && !quote)
// 		{
// 			if (*word == '"')
// 				quote++;
// 			word++;
// 		}
// 		ret[i] = *word;
// 		i++;
// 	}
// 	return (ret);
// }

char	*trim_qoutes(char *word, int index)
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
	while (index--)
		word++;
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
		if (quote)
		{
			ret[i] = *word;
			i++;
		}
		word++;
	}
	return (ret);
}