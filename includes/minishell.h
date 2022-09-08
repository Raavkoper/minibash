/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 11:39:13 by rkoper            #+#    #+#             */
/*   Updated: 2022/09/08 12:13:45 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

int	g_exit_code;

typedef enum e_tokens
{
	PIPE = '|',
	OUTFILE = '>',
	INFILE = '<',
	D_INFILE = 310,
	D_OUTFILE = 312,
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
	char			**command;
	int				has_red;
	struct s_red	*red;
	struct s_parser	*next;
}				t_parser;

typedef struct s_data
{
	t_red		*red;
	t_lexer		*lexer;
	t_parser	*parser;
	int			exit_codes;
	char		**env;
}				t_data;

/* main functions */
char		*init_shell(void);
void		run_shell(t_data *data);

/* lexer functions */
void		lexer(t_data *data, char *str);
char		*mod_substr(char *str, int *i);
void		append_list(t_lexer **lexer, char *str, int *i);
int			check_quotes(char *line);
void		set_quote(char *line, int *quote);
char		*get_string(char *line, int *i);
void		set_node_values(t_lexer **node, char *str, int *i);
char		*quote_substr(char *line, int end);
void		add_quote_index(int quote, char *line, int *x);

/* parser functions */
t_parser	*init_cmdtable(t_parser *parser);
int			count_pipes(t_lexer *lexer);
int			count_commands(t_lexer *lexer);
int			list_len(t_parser *parser);
int			wordcount(char const *s);
void		init_parser(t_parser **parser);
void		add_command(t_parser *parser, char *str, int commands, \
			t_data *data);
void		parser(t_data *data);
void		parser2(t_data *data, int commands);

/* redirection functions */
void		redirections(t_data *data);
int			count_redirections(t_lexer *lexer);
void		init_red(t_red **red);

/* expander functions */
char		*expander(char **env, char *var, t_data *data);
char		*trim_double(char *word, int index);
char		*trim_qoutes(char *word);
char		*cpy_env_var(char **env, char *var, int *x);
char		*add_char(char *str, char c, int *liberate);
char		*dub_min_digit(char *str, int *x);
char		*trim_quotes(char *word, int liberate);
char		*merge_str(char *s1, char *s2);
void		quote_checker(int *sq, int *dq, char c);
int			export_strncmp(const char *s1, const char *s2, size_t n);
void		three_ints_tozero(int *a, int *b, int *c);

/* executor functions */
void		executor(t_data *data);
int			find_command(t_data *data, char *command, char **cmd_table);
int			outfile(t_red *red);
int			check_shell(t_data *data);
int			has_outfile(t_lexer *lexer);
int			check_doubles(t_lexer *lexer);
int			check_file(char *name);
char		*execute(t_parser *parser, char **env);
char		*search_path(char **paths, char *cmdarg);
char		*get_path(char **env);
void		shell_pipex(t_data *data);
void		child_process(t_parser *parser, char **env);
void		create_pipes(int in, int tmpout, t_parser *parser);
void		check_red(t_data **data);
void		check_redirections(t_red *red);
void		end_pipes(char *hid_name, int tmpin, int tmpout);
void		count_exits(t_data *data);

/* heredoc functions */
char		*check_heredoc(t_lexer *lexer);
void		open_heredoc(t_data *data);
void		start_pipes(int *in, int *tmpin, int *tmpout);
int			check_end(char *input, char *filename);
void		executor(t_data *data);
int			find_command(t_data *data, char *command, char **cmd_table);
int			ft_word_check(char const *s);
char		*infile(t_lexer *lexer);
char		*execute(t_parser *parser, char **env);
char		*search_path(char **paths, char *cmdarg);
char		*get_path(char **env);
void		shell_pipex(t_data *data);
void		child_process(t_parser *parser, char **env);
void		create_pipes(int in, int tmpout, t_parser *parser);
void		heredoc(t_data *data, char *hid_name, int *in);

/* builtin functions */
void		ft_env(char **env);
char		**env_dup(char **env, int size);
void		ft_exit(char **cmd_table);
int			ft_exit2(char **cmd_table, char *command, int *exitcode);
void		ft_export(char	***env, char **cmd_table);
void		print_export(char **env);
void		export_add_quotes(char *var);
int			varname_len(char *var);
int			export_var_len(char *str);
char		**sort_env(char **env);
void		export_check_dup(char ***env, char *command);
void		add_line_to_env(char ***env, char *new_var);
void		remove_line_from_env(char ***env, char *var);
void		ft_unset(char ***env, char **cmd_table);
char		*ft_pwd(int status);
void		ft_cd(char ***env, char **cmd_table);
int			change_pwd(char **cmd_table, char **env, char *old_path);
int			change_pwd2(char **cmd_table);
char		*get_old_pwd(char **env);
void		directory_split(void);
void		find_home_dir(char status);
void		ft_echo(char **cmd_table);
void		print_echo(char **cmd_table, int nl);
int			check_add_n(char *str);
int			check_add_chars(char *str);

/* general functions */
int			iswhitespace(char c);
int			istoken(char c);
int			is_double(int c);
int			isquote(char *line);
int			is_redirection(char c);
int			is_is(char *line);
int			dp_len(char **arr);
int			isdollar(char *line);
int			is_wholenum(char *line);

/* free functions */
void		free_lexer(t_lexer **lexer);
void		free_parser(t_parser **parser);
void		free_dp(char **arr);
void		free_redirections(t_red **red);

/* signal functions */
void		handle_signals(void);
void		new_prompt(int sig);

/* error functions */
void		error_check(t_lexer **lexer);
int			valid_token(t_lexer *lexer, int *token);
void		print_error(t_lexer **lexer, int token);
void		*safe_calloc(size_t count, size_t size);
char		*exit_code(t_data *data);

#endif
