/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:27:28 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 12:27:28 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief this functions checks if the char is a valid char
 * @return 0 if its valid 1 if its invalid
 */
int	check_valid_char(char c)
{
	if (ft_strchr("01WNSE \n\r\0", c))
		return (0);
	return (1);
}

int	check_player_char(char c)
{
	if (ft_strchr("WNSE", c))
		return (0);
	return (1);
}

/**
 * @brief checks if all characters of the given map are valid
 *
 * @param map
 * @return 0 if al valid -1 if not
 */
int	handle_char(char **map, t_map *struc, int y, int x)
{
	if (check_valid_char(map[y][x]))
		return (-1);
	if (check_player_char(map[y][x]) == 0)
	{
		if (struc->found_player == 1)
			return (-1);
		struc->player_pos[0] = x;
		struc->player_pos[1] = y;
		struc->direction = map[y][x];
		struc->found_player = 1;
	}
	return (0);
}

int	check_map_chars(char **map, t_map *struc)
{
	int	y;
	int	x;

	y = 0;
	if (!map || !map[y])
		return (-1);
	while (map[y])
	{
		x = 0;
		while (map[y][x])
		{
			if (handle_char(map, struc, y, x) == -1)
				return (-1);
			x++;
		}
		y++;
	}
	return (0);
}

/**
 * @brief checks if the given char is at the end of a line
 *
 * @param line
 * @param index
 * @return 1 if it is 0 if not
 */
int	last_in_line(char *line, int index)
{
	if (!line[index])
		return (0);
	while (line[index])
	{
		if (line[index] != ' ' && line[index] != '\0'
			&& line[index] != '\n' && line[index] != '\r')
			return (0);
		index++;
	}
	return (1);
}
