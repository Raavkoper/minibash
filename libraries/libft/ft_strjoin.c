/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:12:21 by rkoper        #+#    #+#                 */
/*   Updated: 2022/03/25 16:16:17 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
	s3 = ft_calloc(len1 + len2 + 1, sizeof(char));
	if (!s3)
		return (NULL);
	while (i++ < len1)
		s3[i] = s1[i];
	while (j++ < len2)
		s3[i + j] = s2[j];
	return (s3);
}
