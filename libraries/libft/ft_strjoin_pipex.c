/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_pipex.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/19 16:11:45 by cdiks             #+#    #+#             */
/*   Updated: 2022/05/12 10:31:13 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_p(char const *s1, char const *s2)
{
	char	*s3;
	size_t	counter;
	size_t	counter2;
	size_t len1;
	size_t len2;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!s1 || !s2)
		return (NULL);
	counter = 0;
	counter2 = 0;
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (NULL);
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
	s3[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	return (s3);
}
