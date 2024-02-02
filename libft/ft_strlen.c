/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:29:33 by oharoon           #+#    #+#             */
/*   Updated: 2022/11/07 21:12:37 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

/*
#include<string.h>
int main(void)
{
	char *a= "o";
	size_t i = ft_strlen(a);
	printf("%ld\n", i);
	size_t b = strlen(a);
	printf("%ld", b);
}*/