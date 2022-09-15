/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   redirections.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/04 13:10:24 by rkoper        #+#    #+#                 */
/*   Updated: 2022/09/15 14:33:41 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirections(t_data *data)
{
	int			nodes;
	t_red		*red_head;
	t_lexer		*lexer_head;

	data->red = NULL;
	if (!data->lexer)
		return ;
	nodes = count_redirections(data->lexer) + 1;
	while (nodes--)
		init_red(&data->red);
	red_head = data->red;
	lexer_head = data->lexer;
	while (data->lexer)
	{
		red_token_check(data);
		if (data->lexer->token == PIPE)
		{
			data->red->token = PIPE;
			data->red = data->red->next;
		}
		data->lexer = data->lexer->next;
	}
	data->red = red_head;
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
	int	i;

	i = 0;
	while (lexer)
	{
		if ((is_redirection(lexer->token) || is_double(lexer->token) \
			|| lexer->token == PIPE)
			&& lexer->next && lexer->next->command)
			i++;
		lexer = lexer->next;
	}
	return (i);
}

int	count_commands(t_lexer *lexer)
{
	int	i;

	i = 0;
	if (!lexer)
		return (0);
	while (lexer && lexer->token != PIPE)
	{
		if (!lexer->token)
			i += 1;
		if (is_redirection(lexer->token) || is_double(lexer->token))
		{
			if (lexer->next)
				lexer = lexer->next->next;
			else
				lexer = lexer->next;
		}
		else
			lexer = lexer->next;
	}
	return (i);
}

void	count_exits(t_data *data)
{
	t_lexer	*tmp;
	int		i;
	int		exit_codes;

	tmp = data->lexer;
	exit_codes = 0;
	while (data->lexer)
	{
		i = 0;
		if (data->lexer->command)
		{
			if (data->lexer->command[i] == '$'
				&& data->lexer->command[i + 1] == '?')
			{
				exit_codes++;
				i = i + 2;
			}
			i++;
		}
		data->lexer = data->lexer->next;
	}
	data->lexer = tmp;
	data->exit_codes = exit_codes;
}
