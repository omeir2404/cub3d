#include "parsing.h"

#define MAPSIZE 23

/**
 * @brief this functions checks if the char is a valid char
 * @return 0 if its valid 1 if its invalid
*/
int check_valid_char(char c)
{
    if (ft_strchr('01WNSE ', c))// confirm {' '}
        return (0);
    return (1);
}

/**
 * @brief 
 * 
 * @param map 
 * @return int 
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
                return (-1);
            x++;
        }
        y++;
    }
    return (0);
}

int last_in_line(char *line, int index)
{
    while (line[++index])
    {
        if (line[index] != ' ' && line[index] != '\0')
            return (0);
    }
    return (1);
}

int check_surround_char(char **map, int x, int y)
{
    if (x == 0 || y == 0 || x == MAPSIZE || y == (int)ft_strlen(map[x]))
        return (1);
    if (check_valid_char(map[x - 1][y]))
        return (1);
    if (check_valid_char(map[x + 1][y]))
        return 1;
    if (check_valid_char(map[x][y - 1]))
        return 1;
    if (check_valid_char(map[x][y + 1]))
        return 1;
    // Diagonal Checks
    if (check_valid_char(map[x - 1][y - 1]))
        return 1;
    if (check_valid_char(map[x - 1][y + 1]))
        return 1;
    if (check_valid_char(map[x + 1][y - 1]))
        return 1;
    if (check_valid_char(map[x + 1][y + 1]))
        return 1;
    return 0; 
}

int check_surrounded(char **map)
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
            if (!check_valid_char(map[i][j]) && map[i][j] != '1')// all chars besides 1 are surrounded but valid chars
                if (check_surround_char(map, i, j) == 1)//leads to the map is surrounded by '1's
                    return (-1);
            j++;
        }
        i++;
    }
    return (0);
}

int parse_map(char **map)
{
    if (check_map_chars(map) == -1)
    {
        printf("invalid map character\n");
        return (-1);
    }
    if (check_surrounded(map) == -1)
    {
        printf("not properly surrounded\n");
        return (-1);
    }
    printf("all good");
    return (0);
}