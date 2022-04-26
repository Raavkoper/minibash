/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/04/26 14:13:31 by rkoper        #+#    #+#                 */
/*   Updated: 2022/04/26 15:24:04 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

char	*mod_substr(char *str, int *i)
{
	int		start;
	char	*sub;
	int		index;

	start = 0;
	index = 0;
	if (!str)
		return (NULL);
	while (!iswhitespace(str[start]) && str[start] && !istoken(str[start]))
		start++;
	sub = ft_calloc(start + 1, sizeof(char));
	if (!sub)
		return (NULL);
	*i += start;
	while (index < start)
	{
		sub[index] = str[index];
		index++;
	}
	return (sub);
}

void	append_list(t_lexer **lexer, char *str, int *i)
{
	t_lexer	*new_node;
	t_lexer	*last;

	last = *lexer;
	new_node = malloc(sizeof(t_lexer));
	if (!new_node)
		exit(EXIT_FAILURE);
	new_node->token = 0;
	if (!istoken(str[0]))
		new_node->command = mod_substr(str, i);
	else
	{
		new_node->token = str[0];
		new_node->command = NULL;
		*i += 1;
	}
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

void	lexer(t_data *data, char *str)
{
	int i;

	i = 0;
	data->lexer = NULL;
	while (str[i])
	{
		if (iswhitespace(str[i]))
			i++;
		if (!iswhitespace(str[i]))
			append_list(&data->lexer, &str[i], &i);
	}
}

void	print_lexer(t_lexer *lexer)
{
	while (lexer != NULL)
	{
		printf("%s$ %d\n", lexer->command, lexer->token);
		lexer = lexer->next;
	}
}