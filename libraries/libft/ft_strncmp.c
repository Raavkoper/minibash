/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strncmp.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:12:47 by rkoper        #+#    #+#                 */
/*   Updated: 2022/03/25 16:12:48 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	int		a;

	i = 0;
	a = 0;
	if (s1[i] == '\0' && s2[i] == '\0')
		return ((unsigned char)s1[i] - s2[i]);
	while (s1[i] != '\0' && i != n)
	{	
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - s2[i]);
		i++;
	}
	if (s2[i] != '\0' && i != n)
		return ((unsigned char)s1[i] - s2[i]);
	return (a);
}
