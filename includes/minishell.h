#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

# include "../libraries/libft/libft.h"

typedef enum e_tokens
{
	PIPE = '|',
    OUTFILE = '>',
    INFILE = '<',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
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
int		isquote(char *line);
char	*init_shell(void);
void	print_lexer(t_lexer *lexer);
void	run_shell(t_data *data);
int 	check_quotes(char *line);
char	*get_string(char *line, int *i);
char	*quote_substr(char *line, int end);
void	add_quote_index(int quote, char *line, int *x);
void	free_lexer(t_lexer **lexer);
#endif