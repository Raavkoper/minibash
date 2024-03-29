/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:36:55 by rkoper        #+#    #+#                 */
/*   Updated: 2022/07/26 14:23:35 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char ***env, char **cmd_table)
{	
	char	*old_path;
	char	*new_path;

	old_path = safe_calloc(sizeof(char), ft_strlen(ft_pwd(0)) + 8);
	ft_strlcat(old_path, "OLDPWD=", 8);
	ft_strlcat(old_path, ft_pwd(0), 260);
	if (!change_pwd(cmd_table, *env, old_path))
	{
		remove_line_from_env(env, "PWD");
		remove_line_from_env(env, "OLDPWD");
		add_line_to_env(env, old_path);
		new_path = safe_calloc(sizeof(char), ft_strlen(ft_pwd(0)) + 5);
		ft_strlcat(new_path, "PWD=", 8);
		ft_strlcat(new_path, ft_pwd(0), 260);
		add_line_to_env(env, new_path);
		free(new_path);
		free(old_path);
	}
}

int	change_pwd(char **cmd_table, char **env, char *old_path)
{
	if (change_pwd2(cmd_table))
		return (0);
	if (*cmd_table[0] == '-' && !cmd_table[0][1])
	{
		if (chdir(get_old_pwd(env)))
		{
			g_exit_code = 1;
			return (printf("failed to cwd to OLDPWD\n"));
		}
		ft_pwd(1);
	}
	else
	{
		if (chdir(*cmd_table))
		{
			free(old_path);
			g_exit_code = 1;
			return (printf("minishell: cd: %s: No such file or directory\n", \
			*cmd_table));
		}
	}
	return (0);
}

int	change_pwd2(char **cmd_table)
{
	char	*temp;

	if (!*cmd_table || ((*cmd_table[0] == '~' && (!cmd_table[0][1] \
	|| cmd_table[0][1] == '/'))))
	{
		if (!*cmd_table)
		{
			if (chdir(getenv("HOME")))
			{
				g_exit_code = 1;
				return (printf("error near cd\n"));
			}
			return (1);
		}
		temp = ft_strjoin(getenv("HOME"), &cmd_table[0][1]);
		if (chdir(temp))
		{
			free(temp);
			g_exit_code = 1;
			return (printf("cd: %s: No such file or directory\n", temp));
		}
		free(temp);
		return (1);
	}
	return (0);
}

char	*get_old_pwd(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "OLDPWD=", 7))
			return (&env[i][7]);
		i++;
	}
	return (NULL);
}
