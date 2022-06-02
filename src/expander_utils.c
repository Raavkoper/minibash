/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   expander_utils.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/23 10:58:51 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/01 11:22:45 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_char(char *str, char c, int liberate)
{
	int		i;
	char	*ret;

	i = 0;
	ret = safe_calloc(ft_strlen(str) + 2, sizeof(char));
	while (str[i])
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = c;
	if (liberate)
		free(str);
	return (ret);
}

char	*dub_min_digit(char *str, int *x)
{
	char	*ret;
	int		i;
	int		len;

	len = varname_len(str);
	ret = safe_calloc(ft_strlen(str) + 1, sizeof(char));
	i = 0;
	while (i < len)
	{
		ret[i] = str[i];
		i++;
	}
	*x += len + 1;
	return (ret);
}

char	*merge_str(char *s1, char *s2)
{
	char	*s3;
	int		i;
	int		j;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return (NULL);
	i = 0;
	j = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	s3 = safe_calloc(len1 + len2 + 1, sizeof(char));
	while (i < len1)
	{
		s3[i] = s1[i];
		i++;
	}
	while (j < len2)
	{
		s3[i + j] = s2[j];
		j++;
	}
	if (s1[0])
		free(s1);
	if (s2[0])
		free(s2);
	return (s3);
}
