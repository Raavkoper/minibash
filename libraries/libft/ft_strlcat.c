/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:12:25 by rkoper        #+#    #+#                 */
/*   Updated: 2022/03/25 16:12:26 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	d_len;

	d_len = ft_strlen(dst);
	if (dstsize > d_len)
		ft_strlcpy(dst + d_len, src, dstsize - d_len);
	if (dstsize < d_len)
		return (ft_strlen(src) + dstsize);
	return (d_len + ft_strlen(src));
}
