#include "parsing.h"

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
            if (map[i][j] == '0')
                if (check_surround(map, i, j) == -1)
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
