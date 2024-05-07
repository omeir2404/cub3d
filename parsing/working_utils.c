/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   working_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 11:47:34 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 15:41:09 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

/**
 * @brief Get the mapsize of the given map
 * ATTENTION: make sure that the fd is poining  to the start of the map!!
 * 
 * @param fd 
 * @param map 
 */
int	get_map_size(int *fd, t_map *map)
{
	char	*s;

	map->map_size = 1;
	s = get_next_line(*fd);
	while (s && !map_start(s))
	{
		free(s);
		s = get_next_line(*fd);
	}
	if (!map_start(s))
	{
		printf("NO MAP??\n");
		return (-1);
	}
	free(s);
	while (s)
	{
		s = get_next_line(*fd);
		if (s && s[0] != '\n')
			map->map_size++;
		free(s);
	}
	if (s)
		free(s);
	return (0);
}

/**
 * @brief frees a char matrix
 * 
 * @param matrix 
 */
void	free_mat(char **matrix)
{
	int	i;

	i = 0;
	if (!matrix)
		return ;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
	return ;
}

/**
 * @brief copies a matrix
 * ATTENTION: make sure to free afterwards!!
 * @param map 
 * @return the copy
 */
char	**copy_mat(t_map *map)
{
	char	**ret;
	int		i;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (map->map_size + 1));
	while (map->map[i])
	{
		ret[i] = (char *)malloc(sizeof(char) * ft_strlen(map->map[i]));
		ft_strlcpy(ret[i], map->map[i], (int)ft_strlen(map->map[i]));
		i++;
	}
	ret[i] = NULL;
	return (ret);
}

/**
 * @brief indicates if the string given corresponds to the start of a valid map
 * 
 * @return 1 if map started 0 if not
*/
int	map_start(char *s)
{
	int	i;
	int	ones;

	ones = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '1')
			return (1);
		else
			return (0);
		i++;
	}
	return (ones >= 1);
}

/**
 * @brief opens the file given in the stdin and puts the fd into map->fd
 * @return 0 if ok,  -1 if not okat
*/
int	open_file(t_map *map)
{
	map->fd = open(map->file, O_RDONLY);
	if (map->fd == -1)
	{
		perror("file open error in map init\n");
		return (-1);
	}
	return (0);
}
