/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:13:52 by rkoper        #+#    #+#                 */
/*   Updated: 2022/03/25 16:13:53 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*add_buf(char *s1, char *s2)
{
	char	*s3;

	if (!s1)
		s1 = ft_calloc(1, sizeof(char));
	if (!s1 || !s2)
		return (NULL);
	s3 = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!s3)
	{
		free(s1);
		return (NULL);
	}
	s3 = ft_strcpy(s3, s1);
	s3 = ft_strcpy(s3, s2);
	free(s1);
	return (s3);
}

char	*ft_strcpy(char *dst, char *src)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(dst);
	while (src[i])
	{
		dst[len] = src[i];
		i++;
		len++;
	}
	return (dst);
}
