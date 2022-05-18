/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: rkoper <rkoper@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/05/10 13:40:42 by rkoper        #+#    #+#                 */
/*   Updated: 2022/05/18 14:13:42 by rkoper        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_pwd(int status)
{
	char	pwd[260];

	if (status == 1)
		printf("%s\n", getcwd(pwd, sizeof(pwd)));
	if (status == 0)
		return (getcwd(pwd, sizeof(pwd)));
	return (NULL);
}
