/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:25:34 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 15:25:35 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shift_args(t_ast **node)
{
	int	i;

	i = -1;
	while ((*node)->cmd->args[++i])
		(*node)->cmd->args[i] = (*node)->cmd->args[i + 1];
}

int	find_last_index(char **args)
{
	int	last;

	last = 0;
	while (args[last])
		++last;
	return (last);
}
