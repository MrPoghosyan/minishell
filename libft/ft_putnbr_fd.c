/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:01:11 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 15:01:16 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_abs(int c)
{
	if (c < 0)
		return (-c);
	return (c);
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;

	if (n < 0)
		ft_putchar_fd('-', fd);
	c = ft_abs(n % 10) + 48;
	n = ft_abs(n / 10);
	if (n != 0)
		ft_putnbr_fd(n, fd);
	ft_putchar_fd(c, fd);
}
