/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parse2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:37:41 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/08 15:52:24 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief checks if the character at x,y is surrounded by valid characters
 *
 * @param map
 * @param x
 * @param y
 * @param struc
 * @return 0 if it is , 1 if not
 */
int	check_surround_char(char **map, int x, int y, t_map *struc)
{
	if (x == 0 || y == 0 || x == (struc->map_size - 1)
		|| y == (int)ft_strlen(map[x]))
		return (1);
	if (check_valid_char(map[x - 1][y]) || last_in_line(map[x - 1], y))
		return (1);
	if (check_valid_char(map[x + 1][y]) || last_in_line(map[x + 1], y))
		return (1);
	if (check_valid_char(map[x][y - 1]) || last_in_line(map[x], y - 1))
		return (1);
	if (check_valid_char(map[x][y + 1]) || last_in_line(map[x], y + 1))
		return (1);
	if (check_valid_char(map[x - 1][y - 1]) || last_in_line(map[x - 1], y - 1))
		return (1);
	if (check_valid_char(map[x - 1][y + 1]) || last_in_line(map[x - 1], y + 1))
		return (1);
	if (check_valid_char(map[x + 1][y - 1]) || last_in_line(map[x + 1], y - 1))
		return (1);
	if (check_valid_char(map[x + 1][y + 1]) || last_in_line(map[x + 1], y + 1))
		return (1);
	return (0);
}

/**
 * @brief checks if valid characters that need to be surrounded are
 *
 * @param map
 * @param struc
 * @return 0 if they are, 1 if not
 */
int	check_surrounded(char **map, t_map *struc)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (!check_valid_char(map[i][j]) && map[i][j] != '1'
				&& map[i][j] != ' ' && map[i][j] != '\n' && map[i][j] != '\r'
				&& map[i][j] != '\0')
				if (check_surround_char(map, i, j, struc) == 1)
					return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_min(char **map)
{
	int	i;
	int	j;

	j = 0;
	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
			if (map[i][j] == 'W' || map[i][j] == 'N'
				|| map[i][j] == 'S' || map[i][j] == 'E')
				return (0);
	}
	return (-1);
}

/**
 * @brief checks if the map is valid
 *
 * @param map
 * @param struc
 * @return 0 if its valid, -1 if not
 */
int	parse_map(char **map, t_map *struc)
{
	if (!map || !map[0])
		return (-1);
	if (check_map_chars(map, struc) == -1)
		return (-1);
	if (check_surrounded(map, struc) == -1)
		return (-1);
	if (check_min(map) == -1)
		return (-1);
	return (0);
}
