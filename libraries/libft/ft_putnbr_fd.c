/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_putnbr_fd.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:11:59 by rkoper        #+#    #+#                 */
/*   Updated: 2022/03/25 16:12:00 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	long long	l;

	l = (long long)n;
	if (l < 0)
	{
		ft_putchar_fd('-', fd);
		l = l * -1;
	}
	if (l > 9)
	{
		ft_putnbr_fd(l / 10, fd);
		ft_putnbr_fd(l % 10, fd);
	}
	if (l >= 0 && l <= 9)
		ft_putchar_fd(l + '0', fd);
}
