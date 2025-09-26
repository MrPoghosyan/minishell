/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 14:58:24 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 14:58:25 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_num_len(int num)
{
	int	len;

	if (num <= 0)
		len = 1;
	else
		len = 0;
	while (num)
	{
		num /= 10;
		len++;
	}
	return (len);
}

static int	ft_abs(int nbr)
{
	if (nbr < 0)
		return (-nbr);
	return (nbr);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*result;

	len = get_num_len(n);
	result = (char *)malloc(sizeof(char) * (len + 1));
	if (!result)
		return (NULL);
	result[len] = '\0';
	if (n < 0)
		result[0] = '-';
	if (n == 0)
		result[0] = '0';
	while (n)
	{
		result[--len] = ft_abs((n % 10)) + 48;
		n /= 10;
	}
	return (result);
}
