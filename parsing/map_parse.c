#include "parsing.h"


/**
 * @brief this functions checks if the char is a valid char
 * @return 0 if its valid 1 if its invalid
*/
int check_valid_char(char c)
{
    if (ft_strchr("01WNSE \n\r\0", c))// confirm {' '}
        return (0);
    return (1);
}

/**
 * @brief checks if all characters of the given map are valid
 * 
 * @param map 
 * @return 0 if al valid -1 if not
 */
int check_map_chars(char **map)
{
    int y;
    int x;

    y = 0;
    x = 0;
    while(map[y])
    {
        x = 0;
        while(map[y][x])
        {
            if (check_valid_char(map[y][x]))
            {
                printf("\ninvalid map character[%c], y %d, x %d\n", map[y][x], y, x);
                return (-1);
            }
            x++;
        }
        y++;
    }
    return (0);
}

/**
 * @brief checks if the given char is at the end of a line
 * 
 * @param line 
 * @param index 
 * @return 1 if it is 0 if not
 */
int last_in_line(char *line, int index)
{
    while (line[index])
    {
        if (line[index] != ' ' && line[index] != '\0' && line[index] != '\n' && line[index] != '\r')
            return (0);
        index++;
    }
    return (1);
}

/**
 * @brief checks if the character at x,y is surrounded by valid characters
 * 
 * @param map 
 * @param x 
 * @param y 
 * @param struc 
 * @return 0 if it is , 1 if not
 */
int check_surround_char(char **map, int x, int y, t_map *struc)
{
    if (x == 0 || y == 0 || x == struc->mapSize || y == (int)ft_strlen(map[x]))
        return (1);
    if (check_valid_char(map[x - 1][y]) || last_in_line(map[x - 1], y))
        return (1);
    if (check_valid_char(map[x + 1][y]) || last_in_line(map[x + 1], y))
            return (1);
    if (check_valid_char(map[x][y - 1]) || last_in_line(map[x], y - 1))
        return (1);
    if (check_valid_char(map[x][y + 1]) || last_in_line(map[x], y + 1))
        return (1);
    // Diagonal Checks
    if (check_valid_char(map[x - 1][y - 1]) || last_in_line(map[x - 1], y - 1))
        return (1);
    if (check_valid_char(map[x - 1][y + 1]) || last_in_line(map[x - 1], y + 1))
        return (1);
    if (check_valid_char(map[x + 1][y - 1]) || last_in_line(map[x + 1], y - 1))
        return (1);
    if (check_valid_char(map[x + 1][y + 1]) || last_in_line(map[x + 1], y + 1))
        return (1);
    return 0; 
}

/**
 * @brief checks if valid characters that need to be surrounded are 
 * 
 * @param map 
 * @param struc 
 * @return 0 if they are, 1 if not
 */
int check_surrounded(char **map, t_map *struc)
{
    int i;
    int j;

    j = 0;
    i = 0;
    while (map[i])
    {
        j = 0;
        while (map[i][j])
        {
            if (!check_valid_char(map[i][j]) && map[i][j] != '1' && map[i][j] != ' ' && map[i][j] != '\n' && map[i][j] != '\r' )// all chars besides 1 are surrounded but valid chars
                if (check_surround_char(map, i, j, struc) == 1)//leads to the map is surrounded by '1's
                    return (-1);
            j++;
        }
        i++;
    }
    return (0);
}

/**
 * @brief checks if the map is valid
 * 
 * @param map 
 * @param struc 
 * @return 0 if its valid, -1 if not
 */
int parse_map(char **map, t_map *struc)
{
    if (check_map_chars(map) == -1)
        return (-1);
    if (check_surrounded(map, struc) == -1)
    {
        printf("not properly surrounded\n");
        return (-1);
    }
    return (0);
}