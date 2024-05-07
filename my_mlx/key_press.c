#include "my_mlx.h"
#include "../parsing/parsing.h"
#include <math.h>

// void updateColor(t_data *data, t_dda *control)
// {
// 	if (data->map.map[control->mapY][control->mapX] == '1')
// 	{
// 		data->color = 0x00FF0000; // red
// 		if (fabs(data->dirX) < 1e-6 && data->dirY < -0.5)
// 		{
// 			if (control->side == 0)
// 				data->color = 0x000000FF; // blue
// 		}
// 		else if (fabs(data->dirX) < 1e-6 && data->dirY > 0.5)
// 		{
// 			if (control->side == 0)
// 				data->color = 0x00FFFF00; // yellow
// 		}
// 		else if (data->dirX > 0.5 && fabs(data->dirY) < 1e-6)
// 		{
// 			if (control->side == 0)
// 				data->color = 0x00FF00FF; // magenta
// 		}
// 		else if (data->dirX < -0.5 && fabs(data->dirY) < 1e-6)
// 		{
// 			if (control->side == 0)
// 				data->color = 0x00FFA500; // orange
// 		}
// 	}
// }

int handle_keypress(int keycode, t_data *data)
{
	// printf("handling keyPress\n");
	// move forward if no wall in front of you
	if (keycode == XK_Up || keycode == XK_w) // W
	{
		printf("foward\n");
		if (data->map.map[(int)(data->posY + data->dirY * data->moveSpeed)][(int)(data->posX)] != '1')
			data->posY += data->dirY * data->moveSpeed;
		if (data->map.map[(int)(data->posY)][(int)(data->posX + data->dirX * data->moveSpeed)] != '1')
			data->posX += data->dirX * data->moveSpeed;
	}
	// move backwards if no wall behind you
	if (keycode == XK_Down || keycode == XK_s) // S
	{
		printf("backwards\n");
		if (data->map.map[(int)(data->posY - data->dirY * data->moveSpeed)][(int)(data->posX)] != '1')
			data->posY -= data->dirY * data->moveSpeed;
		if (data->map.map[(int)(data->posY)][(int)(data->posX - data->dirX * data->moveSpeed)] != '1')
			data->posX -= data->dirX * data->moveSpeed;
	}

	if (keycode == XK_d) // D
	{
		printf("move right\n");
		if (data->map.map[(int)(data->posY + data->planeY * data->moveSpeed)][(int)(data->posX)] != '1')
			data->posY += data->planeY * data->moveSpeed;
		if (data->map.map[(int)(data->posY)][(int)(data->posX + data->planeX * data->moveSpeed)] != '1')
			data->posX += data->planeX * data->moveSpeed;
	}
	// move backwards if no wall behind you
	if (keycode == XK_a) // A
	{
		printf("move left\n");
		if (data->map.map[(int)(data->posY - data->planeY * data->moveSpeed)][(int)(data->posX)] != '1')
			data->posY -= data->planeY * data->moveSpeed;
		if (data->map.map[(int)(data->posY)][(int)(data->posX - data->planeX * data->moveSpeed)] != '1')
			data->posX -= data->planeX * data->moveSpeed;
	}

	// rotate to the right
	if (keycode == XK_Right)
	{
		printf("look right\n");
		double oldDirY = data->dirY;
		data->dirY = data->dirY * cos(-data->rotSpeed) - data->dirX * sin(-data->rotSpeed);
		data->dirX = oldDirY * sin(-data->rotSpeed) + data->dirX * cos(-data->rotSpeed);
		double oldPlaneY = data->planeY;
		data->planeY = data->planeY * cos(-data->rotSpeed) - data->planeX * sin(-data->rotSpeed);
		data->planeX = oldPlaneY * sin(-data->rotSpeed) + data->planeX * cos(-data->rotSpeed);
		// updateColor(data, &data->control);
	}
	// rotate to the left
	if (keycode == XK_Left)
	{
		printf("look left\n");
		double oldDirY = data->dirY;
		data->dirY = data->dirY * cos(data->rotSpeed) - data->dirX * sin(data->rotSpeed);
		data->dirX = oldDirY * sin(data->rotSpeed) + data->dirX * cos(data->rotSpeed);
		double oldPlaneY = data->planeY;
		data->planeY = data->planeY * cos(data->rotSpeed) - data->planeX * sin(data->rotSpeed);
		data->planeX = oldPlaneY * sin(data->rotSpeed) + data->planeX * cos(data->rotSpeed);
		// updateColor(data, &data->control);
	}

	if (keycode == XK_Escape)
	{
		end_all(data);
	}

	return (0);
}

int end_all(t_data *data)
{
	// for (int i = 0; i < 8; i++)
	// 	free(data->texture[i]);
	int i;

	i = 0;
	while (i < 4)
	{
		if(data->texture[i])
			mlx_destroy_image(data->mlx_ptr, (void *)data->texture[i]);
		i++;
	}
	if (data && data->mlx_ptr && data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->img.img)
		mlx_destroy_image(data->mlx_ptr, data->img.img);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}

	free_mapS(&data->map);

	exit(0);
}