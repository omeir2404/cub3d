/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:17:26 by oharoon           #+#    #+#             */
/*   Updated: 2022/11/07 21:11:44 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	size;

	size = 0;
	while (size < n)
	{
		if (((unsigned char *) s)[size] == (unsigned char)c)
			return ((void *)(s + size));
		size++;
	}
	return (0);
}
