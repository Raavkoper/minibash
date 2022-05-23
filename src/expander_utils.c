/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 10:58:51 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/23 12:36:30 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_char(char *str, char c)
{
	int i;
	char *ret;

	i = 0;
	ret = ft_calloc(ft_strlen(str) + 2, sizeof(char));
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = c;
	if (str[0])
		free(str);
	return (ret);
}

char	*dub_min_digit(char *str, int *x)
{
	char	*ret;
	int		i;
	int		len;

	len = varname_len(str);
	ret = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = str[i];
		i++;
	}
	*x += len + 2;
	return (ret);
}