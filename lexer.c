/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 14:13:31 by rkoper            #+#    #+#             */
/*   Updated: 2022/05/05 10:10:14 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*mod_substr(char *str, int *i)
{
	int		start;
	char	*sub;
	int		x;

	start = 0;
	x = 0;
	if (!str)
		return (NULL);
	while (!iswhitespace(str[start]) && str[start] && !istoken(str[start]))
		start++;
	sub = ft_calloc(start + 1, sizeof(char));
	if (!sub)
		return (NULL);
	*i += start;
	while (x < start)
	{
		sub[x] = str[x];
		x++;
	}
	return (sub);
}

void	append_list(t_lexer **lexer, char *str, int *i)
{
	t_lexer	*new_node;
	t_lexer	*last;
	static int index;

	last = *lexer;
	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->token = 0;
	if (isquote(str))
		new_node->command = get_string(str, i);
	else if (!istoken(str[0]))
		new_node->command = mod_substr(str, i);
	else
	{
		new_node->token = str[0];
		new_node->command = NULL;
		*i += 1;
	}
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
	int i;

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

void	print_lexer(t_lexer *lexer)
{
	if (!lexer)
		printf("lexer empty\n");
	while (lexer != NULL)
	{
		printf("%s$ token ascii -> %d index -> %d\n", lexer->command, lexer->token, lexer->index);
		lexer = lexer->next;
	}
}
