/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/25 16:13:48 by rkoper        #+#    #+#                 */
/*   Updated: 2022/03/25 16:13:49 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_nl(const char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*get_buf(int fd, char *buf)
{
	char	*temp;
	int		i;

	i = 1;
	temp = ft_calloc(BUFFER_SIZE + i, sizeof(char));
	if (!temp)
		return (NULL);
	while (!check_nl(temp) && i > 0)
	{
		i = read(fd, temp, BUFFER_SIZE);
		if (i == -1)
		{
			free(temp);
			return (NULL);
		}
		if (i != BUFFER_SIZE)
			ft_bzero(&temp[i], BUFFER_SIZE - i);
		buf = add_buf(buf, temp);
	}
	free(temp);
	return (buf);
}

char	*get_line(char *buf)
{
	char	*ret;
	int		i;
	int		j;

	i = 0;
	if (buf[i] == '\0')
		return (NULL);
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	ret = ft_calloc(i + 1, sizeof(char));
	if (!ret)
		return (NULL);
	j = 0;
	while (j < i)
	{
		ret[j] = buf[j];
		j++;
	}
	return (ret);
}

char	*get_new_buf(char *buf)
{
	char	*temp;
	int		i;

	i = 0;
	if (buf[i] == '\0')
	{
		free(buf);
		return (NULL);
	}
	while (buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	temp = ft_calloc(ft_strlen(buf) - i + 1, sizeof(char));
	if (!temp)
		return (NULL);
	temp = ft_strcpy(temp, &buf[i]);
	free(buf);
	return (temp);
}

char	*get_next_line(int fd)
{
	char		*ret;
	static char	*buf;

	if (fd == -1 || fd > OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	buf = get_buf(fd, buf);
	if (!buf)
		return (NULL);
	ret = get_line(buf);
	buf = get_new_buf(buf);
	return (ret);
}
