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

#include <math.h>
#include <stdint.h>
#include <sys/time.h>
#include <X11/Xlib.h>

#define SCREENWIDTH 640
#define SCREENHEIGHT 480
#define TEXHEIGHT 64
#define TEXWIDTH 64

typedef struct s_img
{
	void *img;
	char *addr;
	int bits_per_pixel;
	int line_length;
	int endian;
} t_img;

struct s_dda
{
    int width;
    int height;

    double cameraX;
    double rayDirX;
    double rayDirY;
    int mapY;
    int mapX;

    double sideDistX;
    double sideDistY;

    double deltaDistX;
    double deltaDistY;
    double perpWallDist;
    int stepX;
    int stepY;

    int hit;

    int side; 
};
typedef struct s_dda t_dda;

struct s_data
{
    void *mlx_ptr;
    void *win_ptr;

    int floorColor;
    int ceilingColor;

    double posX;
    double posY; // x and y start position
    double dirX;
    double dirY; // initial direction vector
    double planeX;
    double planeY; // the 2d raycaster version of camera plane
    double time;    // time of current frame
    double oldTime; // time of previous frame
    double frameTime;
    int lineHeight;
    int drawStart;
    int drawEnd;
    int color;

    double moveSpeed;
    double rotSpeed;

    uint32_t buffer[SCREENHEIGHT][SCREENWIDTH];
    uint32_t *texture[8];

    t_dda control;
    t_img img;
    t_map map;
};
typedef struct s_data t_data;

int handle_keypress(int keysym, t_data *data);
int end_all(t_data *data);
int loop_handler(t_data *data);
void setupData(t_data *data);
#endif