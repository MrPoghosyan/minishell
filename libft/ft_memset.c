/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:00:18 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 15:00:20 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*byte_ptr;

	byte_ptr = (unsigned char *)b;
	while (len-- > 0)
		byte_ptr[len] = (unsigned char)c;
	return (b);
}
