/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cd.c                                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:36:55 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/10 13:37:29 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_cd(char **cmd_table)
{
	cmd_table++;
	if (!*cmd_table)
		return find_home_dir('c');
	if (chdir(*cmd_table))
		printf("minishell: cd: %s: No such file or directory\n", *cmd_table);
}

void	find_home_dir(char status)
{
	char	pwd[260];
	char	*path;
	char	*new_path;
	int		i;
	int		s_count;


	s_count = 0;
	i = 0;
	path = getcwd(pwd, sizeof(pwd));
	while (path[i])
	{
		if (s_count == 2 && (iswhitespace(path[i]) || path[i] == '/'))
		{
			i++;
			break ;
		}
		if (path[i] == '/')
			s_count++;
		i++;
	}
	i++;
	new_path = ft_calloc(i + 1, sizeof(char));
	ft_strlcpy(new_path, path, i);
	if (status == 'p')
	{
		printf("%s", new_path);
		free(new_path);
		return ;
	}
	if (chdir(new_path))
		printf("error near cd\n");
	free(new_path);
}