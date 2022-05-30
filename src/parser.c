/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: cdiks <cdiks@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/03 13:07:49 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/30 11:37:31 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser(t_data *data)
{
	int			nodes;
	int			commands;
	char		**temp;
	t_parser	*parser_head;
	t_lexer		*lexer_head;

	data->parser = NULL;
	if (!data->lexer)
		return ;
	temp = NULL;
	nodes = count_pipes(data->lexer) + 1;
	while (nodes--)
		init_parser(&data->parser);
	lexer_head = data->lexer;
	parser_head = data->parser;
	while (data->lexer)
	{
		commands = count_commands(data->lexer, data->env);
		while (data->lexer && data->lexer->token != PIPE)
		{
			if (!data->lexer->token)
			{
				if (data->parser->command)
					temp = data->parser->command;
				add_command(data->parser, data->lexer->command, commands, data->env);
				if (temp)
					data->parser->command = temp;
			}
			else if (data->lexer && is_redirection(data->lexer->token))
			{
				if (data->lexer->next)
					data->lexer = data->lexer->next->next;
				else
					data->lexer = data->lexer->next;
				continue ;
			}
			temp = NULL;
			data->lexer = data->lexer->next;
		}
		data->parser = data->parser->next;
		if (data->lexer && data->lexer->token == PIPE)
			data->lexer = data->lexer->next;
	}
	data->lexer = lexer_head;
	data->parser = parser_head;
}

void	add_command(t_parser *parser, char *str, int commands, char **env)
{
	if (parser->command == NULL)
		parser->command = safe_calloc(sizeof(char *), commands + 1);
	while (*parser->command != NULL)
		parser->command++;
	if (isdollar(str))
	{
		*parser->command = expander(env, str);
		if (!parser->command[0][0])
			*parser->command = NULL;
	}
	else
		*parser->command = trim_quotes(str, 0);
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

int	count_commands(t_lexer *lexer, char **env)
{
	int	i;

	i = 0;
	if (!lexer)
		return (0);
	while (lexer && lexer->token != PIPE)
	{
		if (!lexer->token)
			i += 1;
		if (is_redirection(lexer->token))
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

void	print_parser(t_parser *parser)
{
	int		i;
	int		j;
	char	**temp;

	if (!parser)
		return ;
	j = 0;
	while (parser != NULL)
	{
		i = 0;
		if (parser->command)
			temp = parser->command;
		while (*parser->command)
		{
			printf("command table %d command %d = %s\n", j, i, *parser->command);
			parser->command++;
			i++;
		}
		if (temp)
			parser->command = temp;
		temp = NULL;
		j++;
		parser = parser->next;
	}
}
