/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 13:55:39 by oharoon           #+#    #+#             */
/*   Updated: 2022/11/21 13:55:40 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	pointerhandle(unsigned long int nb)
{
	if (nb == 0)
		return (write(1, "(nil)", 5));
	return (write(1, "0x", 2) + converter_ptr(nb, "0123456789abcdef", 16));
}


int	string_handle(char c, va_list	*args)
{
	if (c == '%')
		return (write(1, "%", 1));
	if (c == 'c')
		return (ft_putchar(va_arg(*args, int)));
	if (c == 's')
		return (ft_putstr(va_arg(*args, char *)));
	if (c == 'p')
		return (pointerhandle(va_arg(*args, unsigned long)));
	if (c == 'i' || c == 'd')
		return (converter(va_arg(*args, int), "0123456789", 10));
	if (c == 'u')
		return (converter(va_arg(*args, unsigned int), "0123456789", 10));
	if (c == 'x')
		return (converter(va_arg(*args, unsigned int), "0123456789abcdef", 16));
	if (c == 'X')
		return (converter(va_arg(*args, unsigned int), "0123456789ABCDEF", 16));
	return (0);
}

int	ft_putchar(char c)
{
	return (write(1, &c, 1));
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (!str)
		str = "(null)";
	while (str[i])
		i++;
	return (write(1, str, i));
}


int	converter(double nbr, char *base, double size)
{
	int		count;

	count = 0;
	if (nbr < 0)
	{
		count += write(1, "-", 1);
		nbr = -nbr;
	}
	if (nbr >= size)
		count += converter(nbr / size, base, size);
	count += write(1, &base[((unsigned long) nbr) % ((unsigned long)size)], 1);
	return (count);
}

int	converter_ptr(unsigned long nbr, char *base, unsigned long size)
{
	int		count;

	count = 0;
	if (nbr >= size)
		count += converter_ptr(nbr / size, base, size);
	count += write(1, &base[nbr % size], 1);
	return (count);
}

int	ft_printf(const char *format, ...)
{
	int		count;
	int		size;
	va_list	tab;

	va_start(tab, format);
	count = -1;
	size = 0;
	while (format[++count])
	{
		if (format[count] == '%')
		{
			size += string_handle(format[++count], &tab);
		}
		else
			size += write(1, &format[count], 1);
	}
	va_end(tab);
	return (size);
}
