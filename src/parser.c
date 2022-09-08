/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 13:07:49 by rkoper            #+#    #+#             */
/*   Updated: 2022/09/08 12:03:24 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_data *data)
{
	int			nodes;
	int			commands;
	t_parser	*parser_head;
	t_lexer		*lexer_head;

	data->parser = NULL;
	if (!data->lexer)
		return ;
	nodes = count_pipes(data->lexer) + 1;
	while (nodes--)
		init_parser(&data->parser);
	lexer_head = data->lexer;
	parser_head = data->parser;
	while (data->lexer)
	{
		commands = count_commands(data->lexer);
		parser2(data, commands);
		data->parser = data->parser->next;
		if (data->lexer && data->lexer->token == PIPE)
			data->lexer = data->lexer->next;
	}
	data->lexer = lexer_head;
	data->parser = parser_head;
}

void	parser2(t_data *data, int commands)
{
	while (data->lexer && data->lexer->token != PIPE)
	{
		if (!data->lexer->token)
			add_command(data->parser, data->lexer->command, \
			commands, data);
		else if ((data->lexer && is_redirection(data->lexer->token))
			|| is_double(data->lexer->token))
		{
			// data->parser->red->token = data->lexer->token;
			// data->parser->red->file = data->lexer->next->command;
			data->parser->has_red = 1;
			if (data->lexer->next)
				data->lexer = data->lexer->next->next;
			else
				data->lexer = data->lexer->next;
			continue ;
		}
		data->lexer = data->lexer->next;
	}
}

void	add_command(t_parser *parser, char *str, int commands, t_data *data)
{
	int	i;

	i = 0;
	if (parser->command == NULL)
		parser->command = safe_calloc(sizeof(char *), commands + 1);
	while (*parser->command != NULL)
	{
		parser->command++;
		i++;
	}
	if (isdollar(str))
		*parser->command = expander(data->env, str, data);
	else
		*parser->command = trim_quotes(str, 0);
	if (!parser->command[0][0])
	{
		free(*parser->command);
		*parser->command = NULL;
	}
	while (i--)
		parser->command--;
}

void	init_parser(t_parser **parser)
{
	t_parser	*new_node;
	t_parser	*last;

	last = *parser;
	new_node = malloc(sizeof(t_parser));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->command = NULL;
	new_node->next = NULL;
	new_node->has_red = 0;
	if (*parser == NULL)
	{
		*parser = new_node;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}

int	count_pipes(t_lexer *lexer)
{
	int	i;

	i = 0;
	while (lexer)
	{
		if (lexer->token == PIPE)
			i++;
		lexer = lexer->next;
	}
	return (i);
}
