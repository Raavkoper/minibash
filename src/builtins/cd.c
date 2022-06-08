/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:36:55 by rkoper        #+#    #+#                 */
/*   Updated: 2022/06/07 11:43:08 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char ***env, char **cmd_table)
{	
	char	*old_path;
	char	*new_path;
	int		changed;

	changed = 0;
	old_path = safe_calloc(sizeof(char), ft_strlen(ft_pwd(0)) + 8);
	ft_strlcat(old_path, "OLDPWD=", 8);
	ft_strlcat(old_path, ft_pwd(0), 260);
	if (!*cmd_table || ((*cmd_table[0] == '~' && !cmd_table[1])))
	{
		if (chdir(getenv("HOME")))
		{
			printf("error near cd\n");
			return ;
		}
		changed++;
	}
	if (!changed && *cmd_table[0] == '-' && !cmd_table[0][1])
	{
		if (chdir(get_old_pwd(*env)))
		{
			printf("failed to cwd to OLDPWD\n");
			return ;
		}
		ft_pwd(1);
		changed++;
	}
	if (!changed)
	{
		if (chdir(*cmd_table))
		{
			printf("minishell: cd: %s: No such file or directory\n", *cmd_table);
			free(old_path);
			return ;
		}
		changed++;
	}
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

// void	find_home_dir(char status)
// {
// 	char	pwd[260];
// 	char	*path;
// 	char	*new_path;
// 	int		i;
// 	int		s_count;
// 	s_count = 0;
// 	i = 0;
// 	path = getcwd(pwd, sizeof(pwd));
// 	while (path[i])
// 	{
// 		if (s_count == 2 && (iswhitespace(path[i]) || path[i] == '/'))
// 		{
// 			i++;
// 			break ;
// 		}
// 		if (path[i] == '/')
// 			s_count++;
// 		i++;
// 	}
// 	i++;
// 	new_path = ft_calloc(i + 1, sizeof(char));
// 	ft_strlcpy(new_path, path, i);
// 	if (status == 'p')
// 	{
// 		printf("%s", new_path);
// 		free(new_path);
// 		return ;
// 	}
// 	if (chdir(new_path))
// 		printf("error near cd\n");
// 	free(new_path);
// }