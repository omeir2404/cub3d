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

int main(int argc, char  **argv)
{

    check_args(argc, argv);
    
    return 0;
}
