/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_handlers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:20:29 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 15:20:31 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_cmd_exec(t_ast **node, t_ht *env)
{
	int		status;
	char	*status_str;

	status = execute_command(node, env);
	status_str = ft_itoa(status);
	ht_set(env, ft_strdup("?"), status_str);
	return (status);
}

int	handle_or_exec(t_ast **root, t_ast **node, t_ht *env)
{
	int	status;

	status = execute_ast(root, &(*node)->left, env);
	if (status != 0)
		status = execute_ast(root, &(*node)->right, env);
	return (status);
}

int	handle_and_exec(t_ast **root, t_ast **node, t_ht *env)
{
	int	status;

	status = execute_ast(root, &(*node)->left, env);
	if (status == 0)
		status = execute_ast(root, &(*node)->right, env);
	return (status);
}
