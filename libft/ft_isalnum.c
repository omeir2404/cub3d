/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 11:15:49 by oharoon           #+#    #+#             */
/*   Updated: 2022/11/07 21:15:13 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97) || (c <= 57 && c >= 48))
		return (1);
	else
		return (0);
}

/*
#include<ctype.h>
int	main(void)
{
	int i = ft_isalnum('Z');
	printf("%d\n", i);
	int b = isalnum('Z');
	printf("%d", b);  
}*/