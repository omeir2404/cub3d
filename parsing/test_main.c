#include "parsing.h"


int init_map(t_map *map, char **argv, int argc)
{
    if (check_args(argc, argv) == -1)
        
    map->file = argv[1];
    map->fd = open_file();

    return 0;
}

int main(int argc, char  **argv)
{
    t_map map;
    init_map(&map, argv, argc);
    
    return 0;
}
