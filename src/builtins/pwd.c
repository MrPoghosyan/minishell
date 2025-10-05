/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:22:23 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 15:22:25 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(char **args, t_ht *env)
{
	char	cwd[PATH_MAX];

	(void)args;
	(void)env;
	if (getcwd(cwd, sizeof (cwd)) != NULL)
		ft_putendl_fd(cwd, 1);
	else
		perror("minishell: pwd");
	return (0);
}
