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

void free_mat(char **matrix)
{
	int i;

	i = 0;
	while(matrix[i])
		free(matrix[i++]);
	free(matrix);
	return ;
}


void copy_into_quad(t_map *map, char **mat)
{
	int i;
	int lines;

	i = 0;
	lines = 0;
	// while
	while(lines < map->mapSize)
	{
		while(mat[lines][i])
		{
			map->map[lines][i] = mat[lines][i];
			i++;
		}
		while (i < map->longest_line)
			map->map[lines][i++] = ' ';
		map->map[lines][i] = '\0';
		lines++;
		i = 0;
	}
}

char **copy_mat(t_map *map)
{
	char **ret;
	int i;

	i = 0;
	ret = (char **)malloc(sizeof(char *) * map->mapSize);
	while (map->map[i])
	{
		ret[i] = (char *)malloc(sizeof(char) * ft_strlen(map->map[i]));
		ft_strlcpy(ret[i], map->map[i], (int)ft_strlen(map->map[i]));
		i++;
	}
	return (ret);
}

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
		while (mat[i][size] == ' ' || mat[i][size] == '\n' || mat[i][size] == '\r' || mat[i][size] == '\0')
			size--;
		if (size > map->longest_line)
			map->longest_line = size;
		i++;
	}
	int l = 0;
	// free_mat(map->map);
	// map->map = (char **)malloc(sizeof(char *) * map->mapSize);
	// i = -1;
	// while (++i <= map->mapSize)
	// 	map->map[i] = (char*)malloc(sizeof(char) * map->longest_line);
	copy_into_quad(map, mat);
}

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
 * @return puts the map inHERERERRE: size : 35

to map->map
*/
void allocate_map(t_map *map)
{
	int i;
	char *s;
	int x;

	i = 0;
	x = -1;
	map->map = (char **)malloc(sizeof(char *) * (map->mapSize + 1));// ja aumentei um para o string NULL
	s = get_next_line(map->fd);
	while (s && !map_start(s))
	{
		free(s);
		s = get_next_line(map->fd);
	}
	map->map[i++] = s; 
	// while (map->map[0][++x])
	// 	if (map->map[0][x] == '\n')
	// 		map->map[0][x] = ' ';
	while(i < map->mapSize)
	{
		// map->map = (char *)malloc(sizeof(char) * map->longest_line + 1);
		x = -1;
		map->map[i] = get_next_line(map->fd);//make sure this works
		// while (map->map[i][++x])
		// 	if (map->map[i][x] == '\n')
		// 		map->map[i][x] = ' ';
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

void get_direction(char *s, char **direction)
{
	char *ret;
	// char **matriz;
	// int i;
	// int size;

	// size = 0;
	// matriz = NULL;
	// i = 1;
	// matriz = ft_split((const char *)s, ' ');
	// while (matriz[i])
	// 	size += ft_strlen(matriz[i]);
	// i = 2;
	// ret = malloc(sizeof(char) * size + 1);
	// ft_memcpy(ret, matriz[1], ft_strlen(matriz[1]));
	// while (matriz[i])
	// 	ft_strlcat(ret, matriz[2], ft_strlen(matriz[i]) + ft_strlen(matriz[i - 1]));
	// free_mat(matriz);
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
			(ret)[m++] = (s)[i];
		i++;
	}
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
		if (s[i] == '\n' || s[i] == '\0')
			printf("empty line in map\n");
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
 * @return 0 if map is quad else 1
*/
int is_quad(char **map)
{
	int i;
	int size;
	int size2;

	i = 0;
	size2 = 0;
	size = ft_strlen(map[0]);
	while (map[0][size] == ' ' || map[0][size] == '\n'|| map[0][size] == '\0')
		size--;
	while(map[i])
	{
		size2 = ft_strlen(map[i]);
		while (map[0][size2] == ' ' || map[0][size2] == '\n'|| map[0][size2] == '\0')
			size2--;
		if ( size2 != size)
		{
			printf("\nis not quad (i: %d), %d | %d\n", i, size, size2);
			return (0);
		}
		i++;
	}
	printf("\nis quad\n");
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
	// find_longest_line(map);
	// show_map_info(*map);
	get_mapsize(&map->fd, map);
	close(map->fd);
	if (open_file(map) == 1)
		return (-1);
	allocate_map(map);
	// if (!is_quad(map->map))
	// 	map_quad(map);
	// get_map(map);

	return (0);
}

void free_mapS(t_map *map)
{
	int i;

	i = 0;
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
	while (i <= map->mapSize)
		free(map->map[i++]);
	free(map->map);
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
	parse_map(map.map);
	free_mapS(&map);
}