#include "parsing.h"


void get_mapsize(int *fd, t_map *map)
{
	char c;
	char prev;

	map->mapSize = 0;
	while (read(*fd, &c, 1) > 0)
	{
		if (c == '\n' && prev != '\n')
			map->mapSize++;	
		prev = c;
	}
}
// void longest_line()


/**
 * @return true if map started
*/
int map_start(char *s)
{
	int i;
	int ones;

	ones = 0;
	i = 0;
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
 * @brief allocates the necassary space for the map(trying to read the map from here)
 * @return puts the map into map->map
*/
void allocate_map(t_map *map)
{
	int i;
	char *s;

	i = 0;
	map->map = (char **)malloc(sizeof(char *) * map->mapSize);// ja aumentei um para o string NULL
	s = get_next_line(map->fd);
	while (s && !map_start(s))
	{
		free(s);
		s = get_next_line(map->fd);
	}
	map->map[i++] = s; 
	while(i <= map->mapSize)
	{
		// map->map = (char *)malloc(sizeof(char) * map->longest_line + 1);
		map->map[i] = get_next_line(map->fd);//make sure this works
		i++;
	}
	map->map[i] = NULL;
	return ;
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

void free_mat(char **matrix)
{
	int i;

	i = 0;
	while(matrix[i])
		free(matrix[i++]);
	free(matrix);
	return ;
}

void get_direction(char *s, int size, char **direction)
{
	char *ret;
	char **matriz;

	matriz = NULL;
	matriz = ft_split((const char *)s, ' ');
	ret = malloc(sizeof(char) * ft_strlen(matriz[1]) + 1);
	ft_memcpy(ret, matriz[1], ft_strlen(matriz[1]));
	free_mat(matriz);
	*direction = ret;
}


int collected_info(t_map map)
{
	if (!map.north || !map.south|| !map.east|| !map.west|| !map.floor|| !map.ceiling)
		return (-1);
	return 0;
}

/**
 * @brief attempting to get information in file before the map(INCOMPLETE)
 * @return 0 if okay
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
		if (s[i] == '\n' || s[i] == '\0' || s[i] == '\n')
			printf("empty line in map\n");
		else if(s[i] == 'N' && s[i + 1] == 'O' && s[i + 2] == ' ')
			get_direction(s, ft_strlen(s), &map->north);
		else if(s[i] == 'S' && s[i + 1] == 'O' && s[i + 2] == ' ')
			get_direction(s, ft_strlen(s), &map->south);
		else if(s[i] == 'W' && s[i + 1] == 'E' && s[i + 2] == ' ')
			get_direction(s, ft_strlen(s), &map->west);
		else if(s[i] == 'E' && s[i + 1] == 'A' && s[i + 2] == ' ')
			get_direction(s, ft_strlen(s), &map->east);
		else if(s[i] == 'F' && s[i + 1] == ' ')
			get_direction(s, ft_strlen(s), &map->floor);
		else if(s[i] == 'C' && s[i + 1] == ' ')
			get_direction(s, ft_strlen(s), &map->ceiling);
		else
		{
			printf("line with no valid info??\n");
			return (-1);
		}
		s = get_next_line(map->fd);
	}
	return (0);
}

void show_map_info(t_map map)
{
	int i;

	i = 0;
	if (map.ceiling)
		printf("map.ceiling :%s", map.ceiling);
	if (map.floor)
		printf("map.floor :%s", map.floor);
	if (map.north)
		printf("map.north :%s", map.north);
	if (map.west)
		printf("map.west :%s", map.west);
	if (map.east)
		printf("map.east :%s", map.east);
	if (map.south)
		printf("map.south :%s", map.south);
	while (map.map && map.map[i])
		printf("map.map[%d] :%s",i ,map.map[i++]);
		// printf("map.map[i] :%s" ,map.map[i++]);
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
	// find_longest_line(map);
	show_map_info(*map);
	get_mapsize(&map->fd, map);
	printf("\n\n\n mapsize: %d \n\n\n", map->mapSize);
	close(map->fd);
	if (open_file(map) == 1)
		return (-1);
	allocate_map(map);
	// get_map(map);

	return (0);
}



/**
 * @brief test main 
*/
int main(int argc, char **argv)
{
	t_map map;

	check_args(argc, argv);
	if (map_init(&map, argv) == -1)
		return (-1);
	show_map_info(map);
}