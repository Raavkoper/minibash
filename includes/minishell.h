#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>

# define NC "\x1B[0m"
# define BLUE "\033[0;34m"
# define RED "\x1B[31m"
# define YELLOW "\x1B[33m"
# define GREEN "\033[1m\033[32m"

# define STDIN 0
# define STDOUT 1
# define STDERR 2

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
	int				index;
	struct s_lexer	*next;
}				t_lexer;

typedef struct s_red
{
	int				token;
	char			*file;
	struct s_red	*next;
}				t_red;

typedef struct s_parser
{
	t_red			*red;
	char			**command;
	struct s_parser	*next;
}				t_parser;

typedef struct s_data
{
	t_lexer		*lexer;
	t_parser	*parser;
	t_red		*red;
	char		**env;
}				t_data;

/* main functions */
char	*init_shell(void);
void	run_shell(t_data *data);

/* lexer functions */
void	lexer(t_data *data, char *str);
char	*mod_substr(char *str, int *i);
void	append_list(t_lexer **lexer, char *str, int *i);
void	print_lexer(t_lexer *lexer);
int		check_quotes(char *line);
char	*get_string(char *line, int *i);
char	*quote_substr(char *line, int end);
void	add_quote_index(int quote, char *line, int *x);

/* parser functions */
void	init_parser(t_parser **parser);
int		count_pipes(t_lexer *lexer);
int		count_commands(t_lexer *lexer);
void	add_command(t_parser *parser, char *str, int commands);
void	parser(t_data *data);
void	print_parser(t_parser *parser);

/* redirection functions */
void	redirections(t_data *data);
int		count_redirections(t_lexer *lexer);
void	init_red(t_red **red);
void	print_redirections(t_red *red);

/* executor functions */
void	executor(t_data *data);
int		find_command(t_data *data, char *command, char **cmd_table);
char 	*infile(t_lexer *lexer);
char 	*outfile(t_lexer *lexer);
int		check_file(char filename, char *name);
char	*execute(t_parser *parser, char **env);
char	*search_path(char **paths, char *cmdarg);
char	*get_path(char **env);
void	shell_pipex(t_data *data);
void	child_process(t_parser *parser, char **env);

/* builtin functions */
void	ft_env(char **env);
void	ft_exit(void);
void	ft_pwd(void);
void	ft_cd(char **cmd_table);
void	directory_split(void);
void	find_home_dir(char status);
void	ft_echo(char **cmd_table);
void	putstr_echo(char *word, int index);
int		check_add_chars(char *str);

/* general functions */
int		iswhitespace(char c);
int		istoken(char c);
int		isquote(char *line);
int		is_redirection(char c);

/* free functions */
void	free_redirections(t_red **red);
void	free_lexer(t_lexer **lexer);
void	free_parser(t_parser **parser);
void	free_dp(char **arr);

/* signal functions */
void	handle_signals(void);
void	new_prompt(int sig);

/* error functions */
void    error_check(t_lexer **lexer);
int		check_token(t_lexer **lexer);

#endif
