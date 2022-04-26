/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf_utils.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/24 16:39:06 by rkoper        #+#    #+#                 */
/*   Updated: 2022/03/24 16:40:42 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_uintlen(unsigned int n)
{
	int	i;

	i = 0;
	while (n >= 10)
	{
		n /= 10;
		i++;
	}
	return (i + 1);
}

void	ft_putunbr_fd(unsigned int n, int fd)
{
	if (n > 9)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	if (n >= 0 && n <= 9)
		ft_putchar_fd(n + '0', fd);
}

void	ft_putuhex_fd(unsigned long n, int fd)
{
	if (n >= 16)
	{
		ft_putuhex_fd(n / 16, 1);
		ft_putuhex_fd(n % 16, 1);
	}
	if (n >= 0 && n <= 15)
	{
		if (n >= 0 && n <= 9)
			ft_putchar_fd(n + '0', fd);
		if (n >= 10 && n <= 15)
			ft_putchar_fd(n % 10 + 'A', fd);
	}
}

int	ft_intlen(int n)
{
	int	i;

	i = 0;
	if (n == -2147483648)
		return (ft_putstr_fd("2147483648", 1) + 1);
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

int	ft_hexlen(unsigned long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n /= 16;
		i++;
	}
	return (i);
}
