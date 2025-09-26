/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:18:47 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 15:18:49 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dst_ptr;
	const unsigned char	*src_ptr;

	if (!src && !dst)
		return (dst);
	i = -1;
	dst_ptr = (unsigned char *)dst;
	src_ptr = (const unsigned char *)src;
	while (++i < n)
		dst_ptr[i] = src_ptr[i];
	return (dst);
}
