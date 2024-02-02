/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:39:30 by oharoon           #+#    #+#             */
/*   Updated: 2022/11/07 21:09:30 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		size;
	char	*dupped;

	size = ft_strlen(s);
	dupped = (char *)malloc(size + 1);
	if (!(dupped))
		return (0);
	ft_memcpy(dupped, s, size + 1);
	return (dupped);
}

/*#include <stdio.h>
int main(void)
{
	const char *s = "";
	char *dupped = ft_strdup(s);
	printf("mine: %s\n", dupped);
	dupped = strdup(s);
	printf("og: %s\n", dupped);
}*/