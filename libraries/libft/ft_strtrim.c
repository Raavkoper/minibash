/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:12:58 by rkoper        #+#    #+#                 */
/*   Updated: 2022/03/25 16:12:59 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*is_set(char const *s1, int c)
{
	size_t	i;
	size_t	s_len;

	i = 0;
	s_len = ft_strlen(s1);
	while (i != s_len)
	{
		if (s1[i] == c)
			return ((char *)(s1 + i));
		i++;
	}
	if (s1[i] == c)
		return ((char *)(s1 + i));
	return (NULL);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		len;
	int		i;
	char	*s2;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	i = 0;
	len = ft_strlen(s1);
	while (is_set(set, s1[start]) && s1[start] != '\0')
		start++;
	while (is_set(set, s1[len - 1]) && s1[start] != '\0')
		len--;
	s2 = ft_calloc(len - start + 1, sizeof(char));
	if (!s2)
		return (NULL);
	while (start < len)
	{
		s2[i] = s1[start];
		i++;
		start++;
	}
	return (s2);
}
