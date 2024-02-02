/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 12:10:45 by oharoon           #+#    #+#             */
/*   Updated: 2022/11/07 21:13:38 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + ('a' - 'A'));
	return (c);
}

/*#include <stdio.h>
int main(void)
{
	char ch;
 
	ch = 'M';
	printf("%c in lowercase is represented as  %c",
		   ch, ft_tolower(ch));
 
	return 0;
}*/