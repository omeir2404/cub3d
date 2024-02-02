/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:44:34 by oharoon           #+#    #+#             */
/*   Updated: 2022/11/07 21:11:41 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	c;

	c = 0;
	if (n == 0)
		return (0);
	while (c < n)
	{
		if (((unsigned char *)s1)[c] != ((unsigned char *)s2)[c])
			return (((unsigned char *)s1)[c] - ((unsigned char *)s2)[c]);
		c++;
	}
	return (0);
}
