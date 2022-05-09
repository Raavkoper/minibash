/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtins.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/07 13:22:09 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/09 10:31:36 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "includes/minishell.h"

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
