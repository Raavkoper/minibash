/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_printf.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/24 16:52:22 by rkoper        #+#    #+#                 */
/*   Updated: 2022/03/24 16:55:33 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putlhex_fd(unsigned long n, int fd)
{
	if (n >= 16)
	{
		ft_putlhex_fd(n / 16, 1);
		ft_putlhex_fd(n % 16, 1);
	}
	if (n >= 0 && n <= 15)
	{
		if (n >= 0 && n <= 9)
			ft_putchar_fd(n + '0', fd);
		if (n >= 10 && n <= 15)
			ft_putchar_fd(n % 10 + 'a', fd);
	}
}

int	ft_checkvalue(va_list argptr, char value)
{
	va_list	argcpy;

	if (value == 's')
		return (ft_putstr_fd(va_arg(argptr, char *), 1));
	else if (value == 'd' || value == 'i')
	{
		va_copy(argcpy, argptr);
		ft_putnbr_fd(va_arg(argptr, int), 1);
		return (ft_intlen(va_arg(argcpy, int)));
	}
	else if (value == 'u')
	{
		va_copy(argcpy, argptr);
		ft_putunbr_fd(va_arg(argptr, unsigned int), 1);
		return (ft_uintlen(va_arg(argcpy, unsigned int)));
	}
	else if (value == 'c')
		return (ft_putchar_fd(va_arg(argptr, int), 1));
	else
		return (ft_checkvalue1(argptr, value));
	return (0);
}

int	ft_checkvalue1(va_list argptr, char value)
{
	va_list	argcpy;

	if (value == 'x')
	{
		va_copy(argcpy, argptr);
		ft_putlhex_fd(va_arg(argptr, unsigned int), 1);
		return (ft_hexlen(va_arg(argcpy, unsigned int)));
	}
	else if (value == 'X')
	{
		va_copy(argcpy, argptr);
		ft_putuhex_fd(va_arg(argptr, unsigned int), 1);
		return (ft_hexlen(va_arg(argcpy, unsigned int)));
	}
	else if (value == 'p')
	{
		ft_putstr_fd("0x", 1);
		va_copy(argcpy, argptr);
		ft_putlhex_fd(va_arg(argptr, unsigned long), 1);
		return (ft_hexlen(va_arg(argcpy, unsigned long)) + 2);
	}
	else if (value == '%')
		return (ft_putchar_fd('%', 1));
	return (0);
}

int	ft_printf(const char *str, ...)
{
	va_list	argptr;
	int		retlen;
	int		i;

	i = 0;
	retlen = 0;
	va_start(argptr, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			retlen += ft_checkvalue(argptr, str[i + 1]);
			i++;
		}
		else
		{
			ft_putchar_fd(str[i], 1);
			retlen++;
		}
		i++;
	}
	va_end(argptr);
	return (retlen);
}
