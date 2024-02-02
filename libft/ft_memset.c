/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:36:31 by oharoon           #+#    #+#             */
/*   Updated: 2022/11/07 21:10:27 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	size_t	size;

	size = 0;
	while (size < len)
	{
		((unsigned char *)b)[size] = c;
		size++;
	}
	return (b);
}

/*
int main(void)
{
	char b[] = "hello";
	void *mine = b;
	int m = 65;

	printf("my return value: %p\n", ft_memset(mine, m, 2));
	printf("their return value: %p\n", memset(mine, m, 2));
}*/