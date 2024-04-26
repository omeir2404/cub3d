#ifndef MY_MLX_H
#define MY_MLX_H
#include "../parsing/parsing.h"
#include <stdio.h>
#include <string.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "../DDA/dda.h"

struct s_data
{
    void *mlx_ptr;
    void *win_ptr;

    double posX;
    double posY; // x and y start position
    double dirX;
    double dirY; // initial direction vector
    double planeX;
    double planeY; // the 2d raycaster version of camera plane
    double time;    // time of current frame
    double oldTime; // time of previous frame

    t_dda control;
    t_map map;
};
typedef struct s_data t_data;

int handle_keypress(int keysym, t_data *data);
int end_all(t_data *data);
#endif