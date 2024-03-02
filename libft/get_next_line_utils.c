/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:12:24 by oharoon           #+#    #+#             */
/*   Updated: 2022/12/03 20:34:21 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlen_gnl(char *str)
{
	int	count;

	if (!str)
		return (0);
	count = 0;
	while (str[count] != '\n' && str[count] != '\0')
		count++;
	if (str[count] == '\n')
		count++;
	return (count);
}

int	ft_check_next_line(char *str)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	j = 0;
	while (str[i])
	{
		if (count == 1)
			str[j++] = str[i];
		if (str[i] == '\n')
			count = 1;
		str[i++] = 0;
	}
	return (count);
}

char	*make_line(char *line, char *buff)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	temp = malloc(sizeof(char) * (ft_strlen_gnl(line) + ft_strlen_gnl(buff) + 1));
	while (line && line[i])
	{
		temp[i] = line[i];
		i++;
	}
	j = 0;
	while (buff[j])
	{
		temp[i++] = buff[j];
		if (buff[j++] == '\n')
			break ;
	}
	temp[i] = '\0';
	free(line);
	return (temp);
}
