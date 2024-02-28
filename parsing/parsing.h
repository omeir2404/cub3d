#ifndef PARSING_H
#define PARSING_H
#include "../libft/libft.h"

struct s_map
{
    char **map;
    char *north;
    char *west;
    char *east;
    char *south;
    int fd;
    char *file;
};
typedef struct s_map t_map;


int check_args(int argc, char **argv);
int parse_map(char **map);
#endif