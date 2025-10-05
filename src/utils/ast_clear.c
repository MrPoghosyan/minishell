/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_clear.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:25:05 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 15:25:06 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*free_node(t_ast **node)
{
	if (node && *node)
		free(*node);
	*node = NULL;
	return (NULL);
}

void	*free_ast_node(t_ast **node)
{
	int		i;

	if (!node || !*node)
		return (NULL);
	if ((*node)->cmd)
	{
		ft_lstclear(&(*node)->cmd->redirections, del_redir);
		i = -1;
		if ((*node)->cmd->args)
		{
			while ((*node)->cmd->args[++i])
				ft_free((*node)->cmd->args[i]);
			ft_free((*node)->cmd->args);
		}
		ft_free((*node)->cmd);
	}
	free_ast_node(&(*node)->left);
	free_ast_node(&(*node)->right);
	return (free_node(node));
}
