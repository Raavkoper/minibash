/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdiks <cdiks@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:22:09 by rkoper            #+#    #+#             */
/*   Updated: 2022/05/09 12:49:45 by cdiks            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

void	find_command(t_data *data, char *command)
{
	if (!ft_strncmp(command, "env", 3))
		ft_env(data->env);
	else if (!ft_strncmp(command, "exit", 4))
		ft_exit();
	else if (!ft_strncmp(command, "pwd", 3))
		ft_pwd();
	else if (!ft_strncmp(command, "cd", 2))
		ft_cd();
}

void	ft_env(char **env)
{
	while (*env)
	{
		printf("%s\n", *env);
		env++;
	}
}

void	ft_exit(void)
{
	printf("%scome back soon :)%s\n", BLUE, NC);
	exit(0);
}

void	ft_pwd(void)
{
	char	pwd[256];

	printf("%s\n", getcwd(pwd, sizeof(pwd)));
}

void	ft_cd(void)
{
	directory_split();
	chdir("/Users/cdiks/Desktop");
}

void	directory_split(void)
{
	char	pwd[256];
	char	*path;

	path = getcwd(pwd, sizeof(pwd));
	printf("%s\n", path);
}
