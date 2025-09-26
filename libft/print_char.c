/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vahstepa <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 15:05:19 by vahstepa          #+#    #+#             */
/*   Updated: 2025/09/05 15:05:21 by vahstepa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_char(va_list ap, t_flags flags, const char **format, int *size)
{
	char	c;
	int		padding;

	c = (char)va_arg(ap, int);
	padding = 0;
	if (flags.width > 1)
		padding = flags.width - 1;
	if (!flags.left_align)
		print_padding(padding, ' ', size);
	ft_putchar_fd(c, 1);
	++(*size);
	if (flags.left_align)
		print_padding(padding, ' ', size);
	++(*format);
}

void	print_string(va_list ap, t_flags flags, const char **format, int *size)
{
	char	*str;
	int		len;
	int		padding;

	str = va_arg(ap, char *);
	len = 6;
	if (str)
		len = ft_strlen(str);
	else
		str = "(null)";
	if (flags.precision_specified && flags.precision < len)
		len = flags.precision;
	padding = 0;
	if (flags.width > len)
		padding = flags.width - len;
	if (!flags.left_align)
		print_padding(padding, ' ', size);
	write(1, str, len);
	(*size) += len;
	if (flags.left_align)
		print_padding(padding, ' ', size);
	++(*format);
}
