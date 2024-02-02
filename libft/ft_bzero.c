/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:49:20 by oharoon           #+#    #+#             */
/*   Updated: 2022/11/07 21:12:00 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	if (n != 0)
	{
		while (i < n)
		{
			((unsigned char *)s)[i] = 0;
			i++;
		}
	}
}

/*int main(void)
{
	char b[] = "hello";
	void *mine = b;
	int m = 65;
	ft_bzero(mine, m);
	printf("my return value: %p\n", mine);
	bzero(mine, m);
	printf("their return value: %p\n", mine);
}*/