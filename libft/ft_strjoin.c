/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 14:35:11 by oharoon           #+#    #+#             */
/*   Updated: 2022/10/30 15:12:46 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_string;
	int		count1;
	int		count2;

	count1 = 0;
	count2 = 0;
	new_string = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	if (!new_string)
		return (0);
	while (s1[count1])
	{
		new_string[count1] = s1[count1];
		count1++;
	}
	while (s2[count2])
	{
		new_string[count1] = s2[count2];
		count1++;
		count2++;
	}
	new_string[count1] = '\0';
	return (new_string);
}
