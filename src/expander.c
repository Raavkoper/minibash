/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 12:34:39 by rkoper        #+#    #+#                 */
/*   Updated: 2022/09/26 13:17:45 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expander(char **env, char *var, t_data *data, int liberate)
{
	int		i;
	char	*ret;
	int		sq;
	int		dq;

	three_ints_tozero(&i, &sq, &dq);
	ret = "";
	while (var[i])
	{
		quote_checker(&sq, &dq, var[i]);
		if (var[i] == '$' && ft_isdigit(var[i + 1]) && !sq)
			ret = merge_str(ret, dub_min_digit(&var[i + 2], &i));
		else if (var[i] == '$' && var[i + 1] == '?' && !sq)
		{
			ret = merge_str(ret, exit_code(data));
			i += 2;
		}
		else if (var[i] == '$' && var[i + 1] && \
		!sq && !iswhitespace(var[i + 1]) && var[i + 1] != '"')
			ret = merge_str(ret, cpy_env_var(env, &var[i + 1], &i));
		else
			ret = add_char(ret, var[i], &i);
	}
	return (trim_quotes(ret, liberate));
}

void	quote_checker(int *sq, int *dq, char c)
{
	if (c == '"' && !*sq)
	{
		*dq += 1;
		*dq %= 2;
	}
	if (c == '\'' && !*dq)
	{
		*sq += 1;
		*sq %= 2;
	}
}

char	*cpy_env_var(char **env, char *var, int *x)
{
	int	len;
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
		if (varname_len(env[i]) == len)
		{
			if (!export_strncmp(env[i], var, len))
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
	three_ints_tozero(&count, &i, &quote);
	temp = word;
	while (*word)
	{
		if ((*word == '\'' || *word == '"') && (*word == quote || count == 0))
		{
			quote = *word;
			word++;
			count++;
			count %= 2;
			continue ;
		}
		ret[i++] = *word;
		word++;
	}
	if (liberate)
		free(temp);
	return (ret);
}

void	three_ints_tozero(int *a, int *b, int *c)
{
	*a = 0;
	*b = 0;
	*c = 0;
}
