#ifndef DDA_H
#define DDA_H

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

#endif