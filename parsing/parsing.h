#ifndef PARSING_H
#define PARSING_H
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

// #define malloc(x) 0 // TESTAR PARA TODOS OS MALLOCS SEREM NULOS

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

struct s_control
{
    t_map map;
};
typedef struct s_control t_control;


t_control *get_game_control(); 


int check_args(int argc, char **argv);


int parse_map(char **map);
#endif