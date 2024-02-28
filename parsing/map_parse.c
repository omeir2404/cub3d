#include "parsing.h"

#define MAPSIZE 23
int check_valid_char(char c)
{
    if (c == '0' || c == '1' ||c == 'W' ||c == 'N' ||c == 'E' ||c == 'S' ||c == ' ' )// confirm {' '}
        return (0);
    return (1);
}

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


// int check_limits(char **map)
// {
//     int i;
//     int j;

//     i = 0;
//     j = 0;
//     while(map[i])
//     {
//         while (map[i][j])
//         {
//             if ((check_valid_char(map[i][j]) && map[i][j] != '1' ) && (i == 0 || j == 0 || j == ft_strlen(map[i]) || i == MAPSIZE - 1))
//             j++;
//         }
//         i++;
//     }
// }

int last_in_line(char *line, int index)
{
    while (line[++index])
    {
        if (line[index] != ' ' && line[index] != '\0')
            return (0);
    }
    return (1);
}

int check_surround_char(char **map, int x, int y)//this function need to be better
{// possibly not covering if theres a non 1 char at [map[0][0...]] or at [map[len][0...MAPSIZE]]
    // Check for '1's in the surrounding cells
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
    // if (check_limits(map) == 1)
    //     return 1;
    return 0; // All surrounding characters are valid
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