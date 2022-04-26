/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:10:49 by rkoper        #+#    #+#                 */
/*   Updated: 2022/03/25 16:10:50 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	malloc_check(int n)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	char	*s;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	s = ft_calloc(malloc_check(n) + 1, sizeof(char));
	if (!s)
		return (NULL);
	len = malloc_check(n);
	i = 0;
	if (n == 0)
		s[i] = '0';
	if (n < 0)
	{
		s[i] = '-';
		n = -n;
	}
	while (len >= 0 && n > 0)
	{
		s[len - 1] = (n % 10) + '0';
		n /= 10;
		len--;
	}
	return (s);
}
