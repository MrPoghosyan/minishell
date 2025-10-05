/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_clear.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:22:52 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 15:22:53 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	del_ht_node(t_ht_node *node)
{
	free(node->key);
	if (node->value)
		free(node->value);
	free(node);
}

static void	ht_clear_slot(t_ht_node **lst)
{
	t_ht_node	*temp;

	while (*lst)
	{
		temp = (*lst)->next;
		del_ht_node(*lst);
		*lst = temp;
	}
}

void	ht_clear(t_ht *map)
{
	size_t	i;

	i = -1;
	while (++i < map->size)
		ht_clear_slot(&map->table[i]);
	free(map->table);
}
