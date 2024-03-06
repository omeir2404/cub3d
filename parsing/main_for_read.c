#include "parsing.h"


/**
 * @brief makes a given map(char **) into a quad map, adding spaces when necessary
 * 
 * @param map 
 * @param mat 
 */
void copy_into_quad(t_map *map, char **mat)
{
	int i;
	int lines;
	int lol;

	i = 0;
	lines = 0;
	lol = 0;
	while(lines < map->mapSize)
	{
		while (mat[lines][i] == ' ')
		{
			map->map[lines][lol] = mat[lines][i];
			lol++;
			i++;
		}
		while(mat[lines][i] != '\n' && mat[lines][i] != '\r' && mat[lines][i] != '\0')
		{
			map->map[lines][lol] = mat[lines][i];
			lol++;
			i++;
		}
		while (lol < map->longest_line)
			map->map[lines][lol++] = '1';
		map->map[lines][lol] = '\0';
		lines++;
		i = 0;
		lol = 0;
	}
	map->map[lines] = NULL;
}

void allocate_quad_map(t_map *map)
{
	int i;

	i = 0;
	map->map = (char **)malloc(sizeof(char *) * (map->mapSize + 1));
	while (i < map->mapSize)
		map->map[i++] = (char *)malloc(sizeof(char) * (map->longest_line + 2));
}

/**
 * @brief calculates the size of the map when quad and the calls the function needed to do so
 * ATTENTION: map will need to be freed from copy_map_into_quad function that is called!!
 * @param map 
 */
void map_quad(t_map *map)
{
	char	**mat;
	int i;
	int size;

	i = 0;
	map->longest_line = 0;
	mat = copy_mat(map);
	while(i < map->mapSize)
	{
		size = ft_strlen(mat[i]);
		while (mat[i][size] == '\n' || mat[i][size] == '\r' || mat[i][size] == '\0')
			size--;
		if (size > map->longest_line)
			map->longest_line = size;
		i++;
	}
	free_mat(map->map);
	allocate_quad_map(map);
	copy_into_quad(map, mat);
	free_mat(mat);
}

/**
 * @brief checks if the given map is quad
 * 
 * @return 1 if it is quad, else 0
*/
int is_quad(char **map)
{
	int i;
	int size;
	int size2;

	i = 0;
	size2 = 0;
	size = ft_strlen(map[0]);
	// printf("\n%c\n", map[0][size]);
	while (map[0][size] == ' ' || map[0][size] == '\n'|| map[0][size] == '\0')
		size--;
	while(map[i])
	{
		size2 = ft_strlen(map[i]);
		while (map[i][size2] == ' ' || map[i][size2] == '\n'|| map[i][size2] == '\0')
			size2--;
		if (size2 != size)
			return (0);
		i++;
	}
	return (1);
}

/**
 * @brief initializes the t_map struct with the coressponding values
 * @return 0 if ok, -1 if not
*/
int map_init(t_map *map, char **argv)
{
	map->north = NULL;
	map->south = NULL;
	map->east = NULL;
	map->west = NULL;
	map->ceiling = NULL;
	map->floor = NULL;
	map->map = NULL;

	map->found_direction = 0;
	map->file = argv[1];
	if (open_file(map) == 1)
		return (-1);
	if (get_info(map) == -1)
		return (-1);
	if (get_mapsize(&map->fd, map) == -1)
		return (-1);
	close(map->fd);
	if (open_file(map) == 1)
		return (-1);
	allocate_map(map);
	if (!is_quad(map->map))
		map_quad(map);
	// show_map_info(*map);
	close(map->fd);
	return (0);
}

/**
 * @brief test main 
*/
int main(int argc, char **argv)
{
	t_map map;

	if (check_args(argc, argv) == -1)
	{
		free_mapS(&map);
		return (-1);
	}
	if (map_init(&map, argv) == -1)
	{

		free_mapS(&map);
		return (-1);
	}
	// show_map_info(map);
	parse_map(map.map, &map);
	info_parse(&map);
	free_mapS(&map);
}