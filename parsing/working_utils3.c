/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_utils3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:01:43 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 16:56:13 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Aux function that handles line management for the allocate map function
 * 
 * @param map 
 * @param i 
 * @param ret 
 */
void	handle_line(t_map *map, int *i, int *ret)
{
	int	lol;

	lol = 0;
	map->map[*i] = get_next_line(map->fd);
	while (map->map[*i][lol] == ' ')
		lol++;
	if (lol == (int)ft_strlen(map->map[*i])
		|| !ft_strncmp(map->map[*i], "\n", 1))
		*ret = 0;
}

/**
 * @brief allocates the necessary space for the map,
 * and then read the map into map.map
*/
int	allocate_map(t_map *map)
{
	int		i;
	char	*s;
	int		ret;

	i = 0;
	ret = 1;
	map->map = (char **)malloc(sizeof(char *) * (map->map_size + 1));
	s = get_next_line(map->fd);
	while (s && !map_start(s))
	{
		free(s);
		s = get_next_line(map->fd);
	}
	if (!map_start(s))
		ret = 0;
	map->map[i++] = s;
	while (i < map->map_size)
	{
		handle_line(map, &i, &ret);
		i++;
	}
	map->map[i] = NULL;
	return (ret);
}

/**
 * @brief Aux funct that handles the copying of chars
 * for the getDirection function
 * 
 * @param s 
 * @param ret 
 * @param m 
 * @param i 
 */
void	copy_chars(char *s, char *ret, int *m, int i)
{
	if (s[i] != ' ' && s[i] != '\n' && s[i] != '\r' && s[i] != '\0')
	{
		((unsigned char *)ret)[*m] = ((unsigned char *)s)[i];
		(*m)++;
	}
}

/**
 * @brief Get the path for the given direction from the file
 * 
 * @param s 
 * @param direction 
 */
void	get_direction(char *s, char **direction)
{
	char	*ret;
	int		i;
	int		size;
	int		white;
	int		m;

	size = 0;
	white = 0;
	m = 0;
	while (s[white] == ' ')
		white++;
	i = white + 2;
	while (s[++i])
		if (s[i] != ' ')
			size++;
	ret = ft_calloc(1, size + 1);
	i = white + 2;
	while (s[i])
	{
		copy_chars(s, ret, &m, i);
		i++;
	}
	*direction = ret;
}

int	parser(int argc, char **argv, t_map *map)
{
	struct_init(map, argv);
	if (check_args(argc, argv) == -1)
	{
		printf("Error\n");
		return (-1);
	}
	if (map_init(map) == -1)
	{
		printf("Error\n");
		return (-1);
	}
	if (parse_map(map->map, map) == -1)
	{
		printf("Error\n");
		return (-1);
	}
	if (info_parse(map) == -1)
	{
		printf("Error\n");
		return (-1);
	}
	return (0);
}
