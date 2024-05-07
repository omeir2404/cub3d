/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:25:22 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 16:55:45 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief checks if all needed info is collected
 * 
 * @param map 
 * @return 0 if it is, -1 if not
 */
int	collected_info(t_map map)
{
	if (!map.north || !map.south || !map.east || !map.west
		|| !map.floor || !map.ceiling)
		return (-1);
	return (0);
}

/**
 * @brief Aux function for get info that handles getting the correct direction
 * 
 * @param s 
 * @param map 
 */
int	handle_direction(char *s, t_map *map)
{
	if (s[0] == 'N' && s[1] == 'O' && s[2] == ' ')
		get_direction(s, &map->north);
	else if (s[0] == 'S' && s[1] == 'O' && s[2] == ' ')
		get_direction(s, &map->south);
	else if (s[0] == 'W' && s[1] == 'E' && s[2] == ' ')
		get_direction(s, &map->west);
	else if (s[0] == 'E' && s[1] == 'A' && s[2] == ' ')
		get_direction(s, &map->east);
	else if (s[0] == 'F' && s[1] == ' ')
		get_direction(s, &map->floor);
	else if (s[0] == 'C' && s[1] == ' ')
		get_direction(s, &map->ceiling);
	else
		return (-1);
	return (0);
}

/**
 * @brief saves information in file (before the map) into the struct
 * @return 0 if okay, else -1
*/
int	get_info(t_map *map)
{
	char	*s;
	int		i;

	s = NULL;
	s = get_next_line(map->fd);
	while (s != NULL && collected_info(*map) == -1)
	{
		i = 0;
		while (s[i] == ' ' || s[i] == '\r')
			i++;
		if (!(s[i] == '\n' || s[i] == '\0'))
		{
			if (handle_direction(s + i, map) == -1)
			{
				if (s)
					free(s);
				return (-1);
			}
		}
		free(s);
		s = get_next_line(map->fd);
	}
	if (s)
		free(s);
	return (0);
}

/**
 * @brief prints all map struct info available
 * 
 * @param map 
 */
void	show_map_info(t_map map)
{
	int	i;

	i = 0;
	if (map.ceiling)
		printf("map.ceiling :%s\n", map.ceiling);
	if (map.floor)
		printf("map.floor :%s\n", map.floor);
	if (map.north)
		printf("map.north :%s\n", map.north);
	if (map.west)
		printf("map.west :%s\n", map.west);
	if (map.east)
		printf("map.east :%s\n", map.east);
	if (map.south)
		printf("map.south :%s\n", map.south);
	while (map.map && map.map[i])
		printf("map.map[i] :%s\n", map.map[i++]);
}

/**
 * @brief frees all allocated variables from the map Struct
 * 
 * @param map 
 */
void	free_map_struct(t_map *map)
{
	int	i;

	i = -1;
	if (map->ceiling)
		free(map->ceiling);
	if (map->floor)
		free(map->floor);
	if (map->north)
		free(map->north);
	if (map->west)
		free(map->west);
	if (map->east)
		free(map->east);
	if (map->south)
		free(map->south);
	i = -1;
	if (map->map)
	{
		while (map->map[++i])
			free(map->map[i]);
		free(map->map);
	}
	if (map->fd)
		close(map->fd);
}
