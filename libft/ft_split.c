/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 16:48:03 by oharoon           #+#    #+#             */
/*   Updated: 2022/11/13 11:46:43 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	word_count(char const *s, char c)
{
	int	word;
	int	is_c;

	word = 0;
	is_c = 0;
	while (*s)
	{
		if (*s != c && is_c == 0)
		{
			is_c = 1;
			word++;
		}
		else if (*s == c)
			is_c = 0;
		s++;
	}
	return (word);
}

/*
" gfdg gf"
*/
char	*create_str(char *str, int i, char **lst, char c)
{
	int		count;
	char	*s;

	count = 0;
	while (*str == c && *str)
		str++;
	while (str[count] && str[count] != c)
		count++;
	s = malloc (sizeof(char ) * (count + 1));
	if (!s)
		return (NULL);
	ft_strlcpy(s, str, count + 1);
	lst[i] = s;
	return (str + count);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		index;
	int		size;
	char	*temp;

	index = -1;
	size = word_count(s, c);
	array = malloc(sizeof(char *) * (size + 1));
	if (!s || !array)
		return (0);
	temp = (char *)s;
	while (++index < size)
		temp = create_str(temp, index, array, c);
	array[size] = NULL;
	return (array);
}

/*int	main(void)
{
	char const	*s = "";
	char		c = ' ';
	int i = -1;

	char **split = ft_split(s, c);
	printf("%i\n", word_count(s, c));
	while (split[++i] != NULL)
		printf("%s\n", split[i]);
	printf("n: %s\n", split[i]);	
}*/