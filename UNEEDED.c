
/**
 * @brief iterates the file to get the size of the next line
 * @return size of the line, -1 if there was an error and 0 if there are no more lines
*/
// int find_next_line(int fd)
// {
// 	int i;
// 	char c;
// 	int status;

// 	i = 0;
// 	status = read(fd, &c, 1);
// 	while (status > 0)
// 	{
// 		if (c == '\n' || c == '\r')
// 			return (i);
// 		status = read(fd, &c, 1);
// 	}
// 	if (status == -1 || i == 0 || !read)
// 		return(-1);
// 	return i;
// }

/**
 * @brief uses {@code find_next_line} to calculate the size of the biggest line found if the map
 * @return puts the size found into map->longest_line
*/
// void find_longest_line(t_map *map)
// {
// 	int i;
// 	int lines;

// 	lines = 0;
// 	map->mapSize = 1;
// 	i = find_next_line(map->fd);
// 	while(i >= 0)
// 	{
// 		if (i > map->longest_line)
// 			map->longest_line = i;
// 		i = find_next_line(map->fd);
// 		map->mapSize++;
// 	}
// 	return ;
// }
