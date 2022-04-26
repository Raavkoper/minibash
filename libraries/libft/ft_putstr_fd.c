/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putstr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:12:03 by rkoper        #+#    #+#                 */
/*   Updated: 2022/03/25 16:14:32 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr_fd(char *s, int fd)
{
	int	i;
	int	len;

	if (!s)
		return (ft_putstr_fd("(null)", 1));
	len = ft_strlen(s);
	i = 0;
	while (i != len)
	{
		write (fd, &s[i], 1);
		i++;
	}
	return (i);
}
