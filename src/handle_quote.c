/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   handle_quote.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/02 14:50:17 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/26 11:34:18 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int check_quotes(char *line)
{
	int	i;
	int	quote;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34 || line[i] == 39)
		{
			quote = line[i++];
			while (line[i] != quote && line[i])
				i++;
			if (!line[i])
			{
				printf("No closing quote\n");
				return (1);
			}
		}
		i++;
	}
	return (0);
}

void	add_quote_index(int quote, char *line, int *x)
{
	int	i;

	i = 0;
	line++;
	while (line[i] != quote && line[i])
		i++;
	*x += i + 1;
}

char	*get_string(char *line, int *i)
{
	int	quote;
	int	x;

	x = 0;
	while (line[x])
	{
		if (line[x] == 39)
		{
			quote = 39;
			break ;
		}
		if (line[x] == 34)
		{
			quote = 34;
			break ;
		}
		x++;
	}
	x = 0;
	while (!iswhitespace(line[x]) && line[x])
	{
		if (line[x] == quote)
			add_quote_index(quote, &line[x], &x);
		if (iswhitespace(line[x]))
		{
			x++;
			break ;
		}
		x++;
	}
	*i += x;
	return (quote_substr(line, x));
}

char	*quote_substr(char *line, int end)
{
	int		i;
	char	*ret;

	i = 0;
	ret = safe_calloc(end + 1, sizeof(char));
	while (i < end)
	{
		ret[i] = line[i];
		i++;
	}
	return (ret);
}