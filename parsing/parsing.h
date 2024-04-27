#ifndef PARSING_H
#define PARSING_H
#include "../libft/libft.h"
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../minilibx-linux/mlx.h"

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
    char direction;
    int foundPlayer;
    int playerPos[2];
    int longest_line;
    int mapSize;
};
typedef struct s_map t_map;

// struct s_control
// {
//     t_map map;
// };
// typedef struct s_control t_control;


// t_control *get_game_control(); 

void free_mat(char **matrix);
int check_args(int argc, char **argv);
int info_parse(t_map *map);
int check_file_access(char *file);
int parse_map(char **map, t_map *struc);
int get_mapsize(int *fd, t_map *map);
char **copy_mat(t_map *map);
int map_start(char *s);
int open_file(t_map *map);
int collected_info(t_map map);
int get_info(t_map *map);
void show_map_info(t_map map);
void free_mapS(t_map *map);
int allocate_map(t_map *map);
void get_direction(char *s, char **direction);
int parser(int argc, char **argv, t_map *map);

#endif