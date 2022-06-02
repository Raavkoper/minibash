/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 12:34:39 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/01 11:22:31 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expander(char **env, char *var)
{
	int		i;
	char	*ret;
	int		sq;
	int		dq;

	i = 0;
	sq = 0;
	dq = 0;
	ret = "";
	while (var[i])
	{
		if (var[i] == '"' && !sq)
		{
			dq++;
			dq %= 2;
		}
		if (var[i] == '\'' && !dq)
		{
			sq++;
			sq %= 2;
		}
		if (var[i] == '$' && ft_isdigit(var[i + 1]) && !sq)
			ret = merge_str(ret, dub_min_digit(&var[i + 2], &i));
		if (var[i] == '$' && var[i + 1] && !sq && !iswhitespace(var[i + 1]))
			ret = merge_str(ret, cpy_env_var(env, &var[i + 1], &i));
		else
		{
			ret = add_char(ret, var[i], i);
			i++;
		}
	}
	return (trim_quotes(ret, 1));
}

char	*cpy_env_var(char **env, char *var, int *x)
{
	int	len;
	int	env_len;
	int	i;

	i = 0;
	len = varname_len(var);
	while (i < len && !iswhitespace(var[i]))
		i++;
	if (i != len)
		return ("");
	i = 0;
	while (env[i])
	{
		env_len = varname_len(env[i]);
		if (env_len == len)
		{
			if (!export_strncmp(env[i], var, env_len))
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

char	*trim_quotes(char *word, int liberate)
{
	int		quote;
	int		count;
	char	*ret;
	int		i;
	char	*temp;

	ret = safe_calloc(ft_strlen(word) + 1, sizeof(char));
	count = 0;
	i = 0;
	quote = 0;
	temp = word;
	while (*word)
	{
		if ((*word == SINGLE_QUOTE || *word == DOUBLE_QUOTE) && (*word == quote || count == 0))
		{
			quote = *word;
			word++;
			count++;
			count %= 2;
			continue ;
		}
		ret[i] = *word;
		i++;
		word++;
	}
	if (liberate)
		free(temp);
	return (ret);
}
