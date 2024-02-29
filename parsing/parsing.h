#ifndef PARSING_H
#define PARSING_H
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
struct s_map
{
    char **map;
    char *north;
    char *west;
    char *east;
    char *south;
    char *floor;
    char *ceiling;
    int fd;
    char *file;
    int found_direction;
    int longest_line;
    int mapSize;
};
typedef struct s_map t_map;

struct s_ola{
    t_map map;
};

int check_args(int argc, char **argv);
int parse_map(char **map);
#endif