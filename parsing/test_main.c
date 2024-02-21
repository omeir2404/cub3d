#include "parsing.h"

#define MAPSIZE 10

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
            if (map[y][x] != '0' && map[y][x] != '1' && map[y][x] != 'N'
                && map[y][x] != 'W' && map[y][x] != 'S' && map[y][x] != 'E' && map[y][x] != ' ' && map[y][x] != '\t')
                return (-1);
            x++;
        }
        y++;
    }
    return (0);
}

int check_valid_char(char c)
{
    if (c == '0' || c == '1' ||c == 'W' ||c == 'N' ||c == 'E' ||c == 'S' ||c == ' ' )// confirm {' '}
        return (0);
    return (1);
}

int check_surround_char(char **map, int x, int y)//this function need to be better
{// possibly not covering if theres a non 1 char at [map[0][0...]] or at [map[len][0...MAPSIZE]]
    // Check for '1's in the surrounding cells
    if (x > 0 && check_valid_char(map[x - 1][y]))
        return 1;
    if (x < (int)ft_strlen(map[x]) && check_valid_char(map[x + 1][y]))
        return 1;
    if (y > 0 && check_valid_char(map[x][y - 1]))
        return 1;
    if (y < MAPSIZE && check_valid_char(map[x][y + 1]))
        return 1;
    // Diagonal Checks
    if (x > 0 && y > 0 && check_valid_char(map[x - 1][y - 1]))
        return 1;
    if (x > 0 && y < MAPSIZE && check_valid_char(map[x - 1][y + 1]))
        return 1;
    if (x < (int)ft_strlen(map[x]) && y > 0 && check_valid_char(map[x + 1][y - 1]))
        return 1;
    if (x < (int)ft_strlen(map[x]) && y < MAPSIZE && check_valid_char(map[x + 1][y + 1]))
        return 1;
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
        while (map[i][j])
        {
            if (!check_valid_char(map[i][j]) && map[i][j] != '1')// all chars but 1 are surrounded but valid chars
                if (check_surround_char(map, i, j) == -1)//leads to the map is surrounded by '1's
                    return (-1);
            j++;
        }
        i++;
    }
    return (0);
}

int main(int argc, char  **argv)
{

    check_args(argc, argv);
    
    return 0;
}
