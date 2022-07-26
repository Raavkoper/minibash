/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:13:31 by rkoper            #+#    #+#             */
/*   Updated: 2022/07/26 15:06:10 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*mod_substr(char *str, int *i)
{
	int		start;
	char	*sub;
	int		x;

	start = 0;
	x = 0;
	if (!str)
		return (NULL);
	while (!iswhitespace(str[start]) && str[start] && !istoken(str[start])
		&& !is_double(str[start]))
		start++;
	sub = safe_calloc(start + 1, sizeof(char));
	*i += start;
	while (x < start)
	{
		sub[x] = str[x];
		x++;
	}
	return (sub);
}

void	set_node_values(t_lexer **node, char *str, int *i)
{
	t_lexer	*new_node;

	new_node = *node;
	if (isquote(str))
		new_node->command = get_string(str, i);
	else if (!istoken(str[0]) && !is_double(str[0]))
		new_node->command = mod_substr(str, i);
	else
	{
		if ((str[1] && is_redirection(str[0]) && \
			is_redirection(str[0]) == is_redirection(str[1])) \
			|| is_double(str[0]))
		{
			new_node->token = is_redirection(str[0]) + 250;
			*i += 2;
		}
		else
		{
			new_node->token = str[0];
			*i += 1;
		}
		new_node->command = NULL;
	}
}

void	append_list(t_lexer **lexer, char *str, int *i)
{
	t_lexer		*new_node;
	t_lexer		*last;
	static int	index;

	last = *lexer;
	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->token = 0;
	set_node_values(&new_node, str, i);
	new_node->index = index;
	index++;
	new_node->next = NULL;
	if (*lexer == NULL)
	{
		*lexer = new_node;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}

void	lexer(t_data *data, char *line)
{
	int	i;

	i = 0;
	data->lexer = NULL;
	if (check_quotes(line))
		return ;
	while (line[i])
	{
		if (iswhitespace(line[i]))
			i++;
		if (line[i] && !iswhitespace(line[i]))
			append_list(&data->lexer, &line[i], &i);
	}
}
