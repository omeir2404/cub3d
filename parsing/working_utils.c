#include "parsing.h"

/**
 * @brief Get the mapsize of the given map
 * ATTENTION: make sure that the fd is poining  to the start of the map!!
 * 
 * @param fd 
 * @param map 
 */
int get_mapsize(int *fd, t_map *map)
{
	char *s;

	map->mapSize = 0;
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
	map->mapSize++;
	free(s);
	while (s)
	{
		s = get_next_line(*fd);
		if (s && s[0] != '\n')
			map->mapSize++;	
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
void free_mat(char **matrix)
{
	int i;

	i = 0;
	while(matrix[i])
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
char **copy_mat(t_map *map)
{
	char **ret;
	int i;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * (map->mapSize + 1));
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
int map_start(char *s)
{
	int i;
	int ones;

	ones = 0;
	i = 0;
	if (!s)
		return (0);
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (s[i] == '1')
			return 1;
		else
			return 0;
		i++;
	}
	return (ones >= 1);
}

/**
 * @brief opens the file given in the stdin and puts the fd into map->fd
 * @return 0 if ok,  -1 if not okat
*/
int open_file(t_map *map)
{
	map->fd = open(map->file, O_RDONLY);
	if (map->fd == -1)
	{
		perror("file open error in map init\n");
		return (-1);
	}
	return (0);
}

/**
 * @brief checks if all needed info is collected
 * 
 * @param map 
 * @return 0 if it is, -1 if not
 */
int collected_info(t_map map)
{
	if (!map.north || !map.south|| !map.east|| !map.west|| !map.floor|| !map.ceiling)
		return (-1);
	return 0;
}


/**
 * @brief saves information in file (before the map) into the struct
 * @return 0 if okay, else -1
*/
int get_info(t_map *map)
{
	char *s;
	int i;

	s = get_next_line(map->fd);
	while (s != NULL && collected_info(*map) == -1)
	{
		i = 0;
		while (s[i] == ' ' || s[i] == '\r')
			i++;
		if (s[i] == '\n' || s[i] == '\0')
			printf("empty line in map file\n");
		else if(s[i] == 'N' && s[i + 1] == 'O' && s[i + 2] == ' ')
			get_direction(s, &map->north);
		else if(s[i] == 'S' && s[i + 1] == 'O' && s[i + 2] == ' ')
			get_direction(s, &map->south);
		else if(s[i] == 'W' && s[i + 1] == 'E' && s[i + 2] == ' ')
			get_direction(s, &map->west);
		else if(s[i] == 'E' && s[i + 1] == 'A' && s[i + 2] == ' ')
			get_direction(s, &map->east);
		else if(s[i] == 'F' && s[i + 1] == ' ')
			get_direction(s, &map->floor);
		else if(s[i] == 'C' && s[i + 1] == ' ')
			get_direction(s, &map->ceiling);
		else
		{
			free(s);
			printf("line with no valid info??\n");
			return (-1);
		}
		free(s);
		s = get_next_line(map->fd);
	}
	free(s);
	return (0);
}



/**
 * @brief prints all map struct info available
 * 
 * @param map 
 */
void show_map_info(t_map map)
{
	int i;

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
		printf("map.map[i] :%s\n" ,map.map[i++]);
		// printf("map.map[%d] :%s\n",i++ ,map.map[i]);

}

/**
 * @brief frees all allocated variables from the map Struct
 * 
 * @param map 
 */
void free_mapS(t_map *map)
{
	int i;

	i = -1;
	// char **m;

	// m = map->map;
	// while(++i <= map->mapSize)
	// 	map->map[i] = NULL;
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
/**
 * @brief allocates the necessary space for the map, and then read the map into map.map
*/
int allocate_map(t_map *map)
{
	int i;
	int lol;
	char *s;
	int ret;

	i = 0;
	lol = 0;
	ret = 0;
	map->map = (char **)malloc(sizeof(char *) * (map->mapSize + 1));
	s = get_next_line(map->fd);
	while (s && !map_start(s))
	{
		free(s);
		s = get_next_line(map->fd);
	}
	if (!map_start(s))
	{
		ret = 0;
		printf("NO MAP??\n");
	}
	map->map[i++] = s; 
	while(i < map->mapSize)
	{
		lol = 0;
		map->map[i] = get_next_line(map->fd);
		while(map->map[i][lol] == ' ')
			lol++;
		if (lol == (int)ft_strlen(map->map[i]))
			ret = 0;
		if (!ft_strncmp(map->map[i], "\n", 1))
			ret = 0;
		i++;
	}
	map->map[i] = NULL;
	return (ret);
}

/**
 * @brief Get the path for the given direction from the file
 * 
 * @param s 
 * @param direction 
 */
void get_direction(char *s, char **direction)
{
	char *ret;
	int i;
	int size;
	int white;
	int m;

	size = 0;
	white = 0;
	m = 0;
	while(s[white] == ' ')
		white++;
	i = white + 2;
	while (s[++i])
		if (s[i] != ' ')
			size++;
	ret = ft_calloc(1, size + 1);
	i = white + 2;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\n' && s[i] != '\r' && s[i] != '\0')
		{
			((unsigned char *)ret)[m] = ((unsigned char *)s)[i];
			m++;
		}
		i++;
	}
	*direction = ret;
}