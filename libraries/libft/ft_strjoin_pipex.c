/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin_pipex.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/01/19 16:11:45 by cdiks         #+#    #+#                 */
/*   Updated: 2022/06/03 11:55:44 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*safe_calloc(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (!ptr)
	{
		write(2, "failed to allocate memory\n", 27);
		exit(1);
	}
	return (ptr);
}

char	*ft_strjoin_p(char const *s1, char const *s2)
{
	char	*s3;
	size_t	counter;
	size_t	counter2;
	size_t	len1;
	size_t	len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	counter = 0;
	counter2 = 0;
	s3 = safe_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	while (counter != len1)
	{
		s3[counter] = s1[counter];
		counter++;
	}
	while (counter2 != len2)
	{
		s3[counter + counter2] = s2[counter2];
		counter2++;
	}
	return (s3);
}
