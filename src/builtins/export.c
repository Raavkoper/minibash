/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   export.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:43:47 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/18 15:47:02 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_export(char ***env, char **cmd_table)
{
	if (!*cmd_table)
	{
		print_export(*env);
		return ;
	}
	export_check_dup(env, *cmd_table);
	while (*cmd_table && (ft_isalpha(*cmd_table[0]) || *cmd_table[0] == '_'))
		add_line_to_env(env, *cmd_table++);
	if (*cmd_table && !ft_isalpha(*cmd_table[0]))
		printf("minishell: export: %s: not a valid identifier\n", *cmd_table);
}

char	**sort_env(char **env)
{
	int i;
	int j;
	int i_lowest;
	int diff;
	int len;
	char **env_sorted;

	i_lowest = 0;
	diff = 0;
	j = 0;
	len = dp_len(env);
	env_sorted = ft_calloc(sizeof(char *), (size_t)len + 1);
	if (!env_sorted)
		exit(1);
	while (j < len)
	{
		i = 0;
		while (env[i])
		{
			if (diff < ft_strncmp(env[i_lowest], env[i], 260))
				i_lowest = i;
			i++;
		}
		env_sorted[j] = env[i_lowest];
		env[i_lowest] = "~";
		j++;
	}
	free(env);
	return (env_sorted);
}

void	print_export(char **env)
{
	int i;
	char **env_sorted;

	i = 0;
	env_sorted = sort_env(env_dup(env, dp_len(env) + 1));
	while (env_sorted[i])
	{
		printf("declare -x ");
		export_add_quotes(env[i]);
		i++;
		printf("\n");
	}
	free_dp(env_sorted);
}

void	export_add_quotes(char *var)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (var[i])
	{
		if (var[i - 1] == '=' && j == 0)
		{
			printf("\"");
			j++;
		}
		printf("%c", var[i]);
		if (!var[i + 1] && j == 1)
			printf("\"");
		i++;
	}
}