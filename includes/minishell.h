#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include "../libraries/libft/libft.h"

typedef enum e_tokens
{
	PIPE = '|',
    OUTFILE = '>',
    INFILE = '<',
	SINGLE_QOUTE = '\'',
	DOUBLE_QOUTE = '\"',
}			t_tokens;

typedef struct s_lexer
{
	char			*command;
	int				token;
	struct s_lexer	*next;
}				t_lexer;

typedef struct s_data
{
	t_lexer *lexer;
}				t_data;

void	lexer(t_data *data, char *str);
char	*mod_substr(char *str, int *i);
void	append_list(t_lexer **lexer, char *str, int *i);
int		iswhitespace(char c);
int		istoken(char c);
void	print_lexer(t_lexer *lexer);
#endif