/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 13:07:49 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/03 17:00:39 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	parser(t_data *data)
{
	int nodes;
	int commands;
	char	**temp;
	t_parser	*head;
	
	data->parser = NULL;
	temp = NULL;
	nodes = count_pipes(data->lexer) + 1;
	while (nodes--)
		init_parser(&data->parser);
	head = data->parser;
	while (data->lexer != NULL)
	{
		commands = count_commands(data->lexer);
		while (data->lexer && data->lexer->token != PIPE)
		{
			if (!data->lexer->token)
			{
				if (data->parser->command)
					temp = data->parser->command;
				add_command(data->parser, data->lexer->command, commands);
				if (temp)
					data->parser->command = temp;
			}
			data->lexer = data->lexer->next;
		}
		data->parser = data->parser->next;
		if (data->lexer && data->lexer->token == PIPE)
		{
			data->lexer = data->lexer->next;
		}
	}
	data->parser = head;
}

void	add_command(t_parser *parser, char *str, int commands)
{
	if (parser->command == NULL)
	{
		parser->command = ft_calloc(sizeof(char *), commands + 1);
		if (!parser->command)
			exit(1);
	}
	while (*parser->command != NULL)
		parser->command++;
	*parser->command = ft_strdup(str);
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
	int i;

	i = 0;
	while (lexer)
	{
		if (lexer->token == PIPE)
			i++;
		lexer = lexer->next;
	}
	return (i);
}

int	count_commands(t_lexer *lexer)
{
	int i;

	i = 0;
	if (!lexer)
		return (0);
	while (lexer && lexer->token != PIPE)
	{
		if (!lexer->token)
			i++;
		lexer = lexer->next;
	}
	return (i);
}

void	print_parser(t_parser *parser)
{
	int i;
	int j;

	if (!parser)
		return ;
	j = 0;
	while (parser)
	{
		i = 0;
		while (*parser->command)
		{
			printf("command table %d command %d = %s\n", j, i, *parser->command);
			parser->command++;
			i++;
		}
		j++;
		parser = parser->next;
	}
}