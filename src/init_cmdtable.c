/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   init_cmdtable.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/30 11:15:44 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/02 11:04:53 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

// t_parser *init_cmdtable(t_parser *parserref)
// {
// 	t_parser *parser;
// 	t_parser *cmd_table;
// 	t_parser *temp;
// 	int i;
// 	int j;

// 	parser = parserref;
// 	cmd_table = safe_calloc(list_len(parser) + 1, sizeof(t_parser));
// 	temp = cmd_table;
// 	i = 0;
// 	while (parser)
// 	{
// 		j = 0;
// 		while (parser->command[j])
// 			i += wordcount(parser->command[j++]);
// 		cmd_table->command = safe_calloc(i + 1, sizeof(char *));
// 		fill_commands(cmd_table->command, parser->command);
// 		cmd_table = cmd_table->next;
// 		parser = parser->next;
// 	}
// }

// void	fill_commands(char **dst, char **src)
// {
// 	int i;
// 	int j;

// 	i = 0;
// 	j = 0;
// 	while (src[j])
// 	{
// 		while (src[j][i])
// 		{

// 		}
// 	}
// }

// int	wordcount(char const *s)
// {
// 	int	i;
// 	int	count;

// 	if (!s)
// 		return (0);
// 	i = 0;
// 	count = 0;
// 	if (!iswhitespace(s[i]))
// 		count++;
// 	while (s[i])
// 	{
// 		if (iswhitespace(s[i]))
// 		{
// 			if (!iswhitespace(s[i + 1]) && s[i + 1])
// 				count++;
// 		}
// 		i++;
// 	}
// 	return (count);
// }

// int	list_len(t_parser *parser)
// {
// 	int i;

// 	i = 0;
// 	while (parser)
// 	{
// 		i++;
// 		parser = parser->next;
// 	}
// 	return (i);
// }