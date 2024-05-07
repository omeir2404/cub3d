/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:43:57 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 16:52:28 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief aux function for {@code parse_colors}
 * 
 * @param mat 
 * @param name 
 * @return 0 if okay, -1 if not okay
 */
int	check_color_num(char **mat, char *name)
{
	int	i;
	int	num;

	i = 0;
	num = 0;
	if (!mat)
		return (-1);
	while (mat[i])
	{
		num = ft_atoi(mat[i]);
		if (!(num >= 0 && num <= 255))
		{
			printf("number out of range for %s color\n", name);
			return (-1);
		}
		i++;
	}
	return (0);
}

/**
 * @brief checks if the colors of the floor and ceiling recieved are in range
 * 
 * @param map 
 * @return 0 if all okay, -1 if not
 */
int	parse_colors(t_map *map)
{
	char	**f;
	char	**c;
	int		ret;

	ret = 0;
	f = ft_split(map->floor, ',');
	c = ft_split(map->ceiling, ',');
	if (check_color_num(f, "floor") == -1)
		ret = -1;
	if (check_color_num(c, "ceiling") == -1)
		ret = -1;
	free_mat(f);
	free_mat(c);
	return (ret);
}

/**
 * @brief parses info recieved from map file (colors and paths)
 * 
 * @param map 
 * @return 0 if all okay, -1 if not
 */
int	info_parse(t_map *map)
{
	if (parse_colors(map) == -1)
		return (-1);
	if (check_file_access(map->north) == -1
		|| check_file_access(map->south) == -1
		|| check_file_access(map->east) == -1
		|| check_file_access(map->west) == -1)
		return (-1);
	return (0);
}

void	struct_init(t_map *map, char **argv)
{
	map->north = NULL;
	map->south = NULL;
	map->east = NULL;
	map->west = NULL;
	map->ceiling = NULL;
	map->floor = NULL;
	map->map = NULL;
	map->direction = 0;
	map->found_direction = 0;
	map->found_player = 0;
	map->file = argv[1];
}

/**
 * @brief initializes the t_map struct with the coressponding values
 * @return 0 if ok, -1 if not
 */
int	map_init(t_map *map)
{
	if (open_file(map) == 1)
		return (-1);
	if (get_info(map) == -1)
		return (-1);
	if (get_map_size(&map->fd, map) == -1)
		return (-1);
	close(map->fd);
	if (open_file(map) == 1)
		return (-1);
	if (allocate_map(map) == -1)
		return (-1);
	if (!is_quad(map->map))
		if (map_quad(map) == -1)
			return (-1);
	close(map->fd);
	return (0);
}
