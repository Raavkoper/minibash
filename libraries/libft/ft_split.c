/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:12:07 by rkoper        #+#    #+#                 */
/*   Updated: 2022/03/25 16:12:08 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_sub_check(char const *s, char const c)
{
	int	i;
	int	j;

	if (!s)
		return (0);
	j = 0;
	i = 0;
	while (s[i] == c)
		i++;
	while (s[i] != c && s[i] != '\0')
	{
		i++;
		j++;
	}
	return (j);
}

static int	ft_word_check(char const *s, char const c)
{
	int	i;
	int	count;

	if (!s)
		return (0);
	i = 0;
	count = 0;
	if (s[i] != c)
		count++;
	while (s[i] != '\0')
	{
		if (s[i] == c)
		{
			if (s[i + 1] != c && s[i + 1] != '\0')
				count++;
		}
		i++;
	}
	return (count);
}

static char	**ft_free(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	return (NULL);
}

char	**ft_split(char const *s, char const c)
{
	int		is_sub;
	int		i;
	int		j;
	char	**arr;

	arr = ft_calloc(ft_word_check(s, c) + 1, sizeof(char *));
	if (!arr)
		return (NULL);
	i = 0;
	j = 0;
	while (j < ft_word_check(s, c) && s[i] != '\0')
	{
		is_sub = 0;
		if (s[i] != c)
		{
			is_sub = ft_sub_check(&s[i], c);
			arr[j] = ft_calloc(is_sub + 1, sizeof(char));
			if (!arr[j])
				return (ft_free(arr));
			ft_strlcpy(arr[j], &s[i], is_sub + 1);
			j++;
		}
		i += is_sub + 1;
	}
	return (arr);
}
