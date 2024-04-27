#include "my_mlx.h"
#include "../parsing/parsing.h"
#include <math.h>

int handle_keypress(int keycode, t_data *data)
{
  printf("handling keyPress\n");
  // move forward if no wall in front of you
  if (keycode == XK_Up)
  {
    printf("foward\n");
    if (data->map.map[(int)(data->posY + data->dirY * data->moveSpeed)][(int)(data->posX)] == 0)
      data->posY += data->dirY * data->moveSpeed;
    if (data->map.map[(int)(data->posY)][(int)(data->posX + data->dirX * data->moveSpeed)] == 0)
      data->posX += data->dirX * data->moveSpeed;
  }
  // move backwards if no wall behind you
  if (keycode == XK_Down)
  {
    printf("backwards\n");
    if (data->map.map[(int)(data->posY - data->dirY * data->moveSpeed)][(int)(data->posX)] == 0)
      data->posY -= data->dirY * data->moveSpeed;
    if (data->map.map[(int)(data->posY)][(int)(data->posX - data->dirX * data->moveSpeed)] == 0)
      data->posX -= data->dirX * data->moveSpeed;
  }
  // rotate to the right
  if (keycode == XK_Right)
  {
    printf("right\n");
    double oldDirY = data->dirY;
    data->dirY = data->dirY * cos(-data->rotSpeed) - data->dirX * sin(-data->rotSpeed);
    data->dirX = oldDirY * sin(-data->rotSpeed) + data->dirX * cos(-data->rotSpeed);
    double oldPlaneY = data->planeY;
    data->planeY = data->planeY * cos(-data->rotSpeed) - data->planeX * sin(-data->rotSpeed);
    data->planeX = oldPlaneY * sin(-data->rotSpeed) + data->planeX * cos(-data->rotSpeed);
  }
  // rotate to the left
  if (keycode == XK_Left)
  {
    printf("left\n");
    double oldDirY = data->dirY;
    data->dirY = data->dirY * cos(data->rotSpeed) - data->dirX * sin(data->rotSpeed);
    data->dirX = oldDirY * sin(data->rotSpeed) + data->dirX * cos(data->rotSpeed);
    double oldPlaneY = data->planeY;
    data->planeY = data->planeY * cos(data->rotSpeed) - data->planeX * sin(data->rotSpeed);
    data->planeX = oldPlaneY * sin(data->rotSpeed) + data->planeX * cos(data->rotSpeed);
  }

  return (0);
}

int end_all(t_data *data)
{
  free_mapS(&data->map);
  mlx_destroy_window(data->mlx_ptr, data->win_ptr);
  // if (data->mlx_ptr)
  // 	free(data->mlx_ptr);
  // mlx_destroy_display(data->mlx_ptr);
  return (0);
}