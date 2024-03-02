#include "parsing.h"

/**
 * @brief iterates the file to get the size of the next line
 * @return size of the line, -1 if there was an error and 0 if there are no more lines
*/
int find_next_line(int fd)
{
	int i;
	char c;
	int status;

	i = 0;
	status = read(fd, &c, 1);
	while (status > 0)
	{
		if (c == '\n')
			return (i);
		status = read(fd, &c, 1);
	}
	if (status == -1 || i == 0 || !read)
		return(-1);
	return 0;
}

/**
 * @brief uses {@code find_next_line} to calculate the size of the biggest line found if the map
 * @return puts the size found into map->longest_line
*/
void find_longest_line(t_map *map)
{
	int i;
	int lines;

	lines = 0;
	map->mapSize = 1;
	i = find_next_line(map->fd);
	while(i > 0)
	{
		if (i > map->longest_line)
			map->longest_line = i;
		i = find_next_line(map->fd);
		map->mapSize++;
	}
	return ;
}

/**
 * @brief allocates the necassary space for the map(trying to read the map from here)
 * @return puts the map into map->map
*/
void allocate_map(t_map *map)
{
	int i;

	i = 0;
	map->map = (char **)malloc(sizeof(char *) * map->mapSize + 1);
	while(i <= map->mapSize)
	{
		// map->map = (char *)malloc(sizeof(char) * map->longest_line + 1);
		map->map[i] = get_next_line(map->fd);//make sure this works
		i++;
	}
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

// int get_map(t_map *map)
// {
//     map->map = get_next_line();
// }

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
		if (s[i] == 1)
			ones++;
		i++;
	}

	return (ones >= 2);
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
	while (s != NULL && !map_start(s) && collected_info(*map) == -1)
	{
		i = 0;
		while (s[i] == ' ')
			i++;
			// if (s[i] == ' ')
			//     i++;
		if (s[i] == '\n' || s[i] == '\0')
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

/**
 * @brief initializes the t_map struct with the coressponding values
 * @return 0 if ok, -1 if not
*/
int map_init(t_map *map, char **argv)
{
	map->found_direction = 0;
	map->file = argv[1];
	if (open_file(map) == 1)
		return (-1);
	if (get_info(map) == -1)
		return (-1);
	find_longest_line(map);
	allocate_map(map);
	close(map->fd);
	// if (open_file(map) == 1)
	// 	return (-1);
	// get_map(map);

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