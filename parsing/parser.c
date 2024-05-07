/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 13:02:41 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 15:45:06 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	copy_and_fill(t_map *map, char **mat, int lines, t_indices *indices)
{
	while (mat[lines][indices->i] == ' ' || (mat[lines][indices->i] != '\n'
		&& mat[lines][indices->i] != '\r' && mat[lines][indices->i] != '\0'))
	{
		map->map[lines][indices->lol] = mat[lines][indices->i];
		indices->lol++;
		indices->i++;
	}
	while (indices->lol < map->longest_line)
		map->map[lines][indices->lol++] = '1';
	map->map[lines][indices->lol] = '\0';
}

/**
 * @brief makes a given map(char **) into a quad map,
 * adding spaces when necessary
 *
 * @param map
 * @param mat
 */
void	copy_into_quad(t_map *map, char **mat)
{
	t_indices	indices;
	int			lines;

	lines = 0;
	while (lines < map->map_size)
	{
		indices.i = 0;
		indices.lol = 0;
		copy_and_fill(map, mat, lines, &indices);
		lines++;
	}
	map->map[lines] = NULL;
}

void	allocate_quad_map(t_map *map, char ***mat)
{
	int	i;

	i = 0;
	free_mat(map->map);
	map->map = (char **)malloc(sizeof(char *) * (map->map_size + 1));
	while (i < map->map_size)
		map->map[i++] = (char *)malloc(sizeof(char) * (map->longest_line + 2));
	copy_into_quad(map, *mat);
	free_mat(*mat);
}

/**
 * @brief calculates the size of the map when 
 * quad and the calls the function needed to do so
 * ATTENTION: map will need to be freed from
 * copy_map_into_quad function that is called!!
 * @param map
 */
int	map_quad(t_map *map)
{
	char	**mat;
	int		i;
	int		size;

	i = 0;
	map->longest_line = 0;
	mat = copy_mat(map);
	if (!mat)
		return (-1);
	while (i < map->map_size)
	{
		if (!mat[i])
			return (-1);
		size = ft_strlen(mat[i]);
		while (mat[i][size] == '\n' || mat[i][size] == '\r'
			|| mat[i][size] == '\0')
			size--;
		if (size > map->longest_line)
			map->longest_line = size;
		i++;
	}
	allocate_quad_map(map, &mat);
	return (0);
}

/**
 * @brief checks if the given map is quad
 *
 * @return 1 if it is quad, else 0
 */
int	is_quad(char **map)
{
	int	i;
	int	size;
	int	size2;

	i = 0;
	size2 = 0;
	size = ft_strlen(map[0]);
	while (map[0][size] == ' ' || map[0][size] == '\n' || map[0][size] == '\0')
		size--;
	while (map[i])
	{
		size2 = ft_strlen(map[i]);
		if (size2 == 0 || size2 == 1)
			return (-1);
		while (map[i][size2] == ' ' || map[i][size2] == '\n'
			|| map[i][size2] == '\0')
			size2--;
		if (size2 != size)
			return (0);
		i++;
	}
	return (1);
}
