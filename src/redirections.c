/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 13:10:24 by rkoper            #+#    #+#             */
/*   Updated: 2022/06/03 14:02:52 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirections(t_data *data)
{
	int 		nodes;
	t_red		*red_head;
	t_lexer		*lexer_head;
	
	data->parser->red = NULL;
	if (!data->lexer)
		return ;
	nodes = count_redirections(data->lexer) + 1;
	while (nodes--)
		init_red(&data->parser->red);
	red_head = data->parser->red;
	lexer_head = data->lexer;
	while (data->lexer)
	{
		if (is_redirection(data->lexer->token) || is_double(data->lexer->token))
		{
			data->parser->red->token = data->lexer->token;
			if (data->lexer->next && data->lexer->next->command)
				data->parser->red->file = ft_strdup(data->lexer->next->command);
			data->parser->red = data->parser->red->next;
		}
		data->lexer = data->lexer->next;
	}
	data->parser->red = red_head;
	data->lexer = lexer_head;
}

void	init_red(t_red **red)
{
	t_red	*new_node;
	t_red	*last;

	last = *red;
	new_node = malloc(sizeof(t_red));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->file = NULL;
	new_node->token = 0;
	new_node->next = NULL;
	if (*red == NULL)
	{
		*red = new_node;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}

int	count_redirections(t_lexer *lexer)
{
	int i;

	i = 0;
	while (lexer)
	{
		if ((is_redirection(lexer->token) || is_double(lexer->token)) 
			&& lexer->next && lexer->next->command)
			i++;
		lexer = lexer->next;
	}
	return (i);
}

void	print_redirections(t_red *red)
{
	if (!red)
		return ;
	while (red)
	{
		printf("red -> %d file name -> %s\n", red->token, red->file);
		red = red->next;
	}
}
