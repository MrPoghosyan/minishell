/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:56:58 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 14:57:00 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*allocated;
	size_t	mul;

	mul = size * count;
	if (mul / size != count)
		return (NULL);
	allocated = malloc(count * size);
	if (!allocated)
		return (NULL);
	ft_bzero(allocated, size * count);
	return (allocated);
}
