/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:09:28 by oharoon           #+#    #+#             */
/*   Updated: 2022/11/07 21:13:45 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - ('a' - 'A'));
	return (c);
}

/*#include <stdio.h>
int main(void)
{
	char ch;
 
	ch = 'g';
	printf("%c in uppercase is represented as  %c",
		   ch, ft_toupper(ch));
 
	return 0;
}*/