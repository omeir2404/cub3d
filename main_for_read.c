#include "parsing/parsing.h"
#include "my_mlx/my_mlx.h"
#include <X11/keysym.h>
#include <math.h>
#include <sys/time.h>
#include <X11/Xlib.h>

void square(t_data *data)
{
	for (int i = 100; i < 200; i++)
		for (int j = 100; j < 200; j++)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, 0x00FF0000);
}

void setupControl(t_dda *control)
{
	control->width = 0;
	control->height = 0;
	control->cameraX = 0;
	control->rayDirX = 0;
	control->rayDirY = 0;
	control->mapY = 0;
	control->mapX = 0;
	control->sideDistX = 0;
	control->sideDistY = 0;
	control->deltaDistX = 0;
	control->deltaDistY = 0;
	control->perpWallDist = 0;
	control->stepX = 0;
	control->stepY = 0;
	control->hit = 0;
	control->side = 0;
}

void setupData(t_data *data)
{
	data->posX = data->map.playerPos[0];
	data->posY = data->map.playerPos[1];
	if (data->map.direction == 'N')
	{
		data->dirX = 0;
		data->dirY = -1;
	}
	else if (data->map.direction == 'S')
	{
		data->dirX = 0;
		data->dirY = 1;
	}

	else if (data->map.direction == 'E')
	{
		data->dirX = 1;
		data->dirY = 0;
	}
	else if (data->map.direction == 'W')
	{
		data->dirX = -1;
		data->dirY = 0;
	}
	data->planeX = data->dirY;
	data->planeX = -data->dirY;
	data->planeY = data->dirX;
	data->time = 0;
	data->oldTime = 0;
	setupControl(&data->control);
}

void DDA(t_dda *control, t_data *data)
{
	// perform DDA
	while (control->hit == 0)
	{
		// jump to next map square, either in x-direction, or in y-direction
		if (control->sideDistX < control->sideDistY)
		{
			control->sideDistX += control->deltaDistX;
			control->mapX += control->stepX;
			control->side = 0;
		}
		else
		{
			control->sideDistY += control->deltaDistY;
			control->mapY += control->stepY;
			control->side = 1;
		}
		// Check if ray has hit a wall
		if ((data->map.map[control->mapY][control->mapX]) == '1')
			control->hit = 1;
	}
}

void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void verLine(int x, int start, int end, int color, t_data *data)
{
	for (int y = start; y < end; y++)
		my_mlx_pixel_put(&data->img, x, y, color);
}

void raycastingLoop(t_dda *control, t_data *data)
{

	for (int x = 0; x < control->width; x++)
	{
		control->cameraX = 2 * x / (double)control->width - 1; // x-coordinate in camera space
		control->rayDirX = data->dirX + data->planeX * control->cameraX;
		control->rayDirY = data->dirY + data->planeY * control->cameraX;
		// which box of the map we're in
		control->mapY = (int)data->posY;
		control->mapX = (int)data->posX;

		// length of ray from current position to next x or y-side
		control->sideDistX;
		control->sideDistY;

		// length of ray from one x or y-side to next x or y-side
		control->deltaDistX;
		if (control->rayDirX == 0) // If ray is vertical, set a very large number to avoid division by zero
			control->deltaDistX = 1e30;
		else // Otherwise, calculate the absolute value of the reciprocal of control->rayDirX
			control->deltaDistX = fabs(1 / control->rayDirX);
		control->deltaDistY;
		if (control->rayDirY == 0) // If ray is horizontal, set a very large number to avoid division by zero
			control->deltaDistY = 1e30;
		else // Otherwise, calculate the absolute value of the reciprocal of control->rayDirY
			control->deltaDistY = fabs(1 / control->rayDirY);
		control->perpWallDist; // later used for length of the ray

		// Determine the direction to step in x or y-direction (either +1 or -1)
		control->stepX;
		control->stepY;

		control->hit = 0; // was there a wall hit?
		control->side;	  // was a NS or a EW wall hit?

		// calculate step and initial sideDist
		if (control->rayDirX < 0)
		{
			control->stepX = -1;
			control->sideDistX = (data->posX - control->mapX) * control->deltaDistX;
		}
		else
		{
			control->stepX = 1;
			control->sideDistX = (control->mapX + 1.0 - data->posX) * control->deltaDistX;
		}
		if (control->rayDirY < 0)
		{
			control->stepY = -1;
			control->sideDistY = (data->posY - control->mapY) * control->deltaDistY;
		}
		else
		{
			control->stepY = 1;
			control->sideDistY = (control->mapY + 1.0 - data->posY) * control->deltaDistY;
		}
		DDA(control, data);
		// Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
		if (control->side == 0)
			control->perpWallDist = (control->sideDistX - control->deltaDistX);
		else
			control->perpWallDist = (control->sideDistY - control->deltaDistY);

		// Calculate height of line to draw on screen
		int lineHeight = (int)(control->height / control->perpWallDist);

		// calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + control->height / 2;
		if (drawStart < 0)
			drawStart = 0;
		int drawEnd = lineHeight / 2 + control->height / 2;
		if (drawEnd >= control->height)
			drawEnd = control->height - 1;

		// choose wall color
		int color;
		switch (data->map.map[control->mapY][control->mapX])
		{
		case 1:
			color = 0x00FF0000;
			break; // red
		case 2:
			color = 0x0000FF00;
			break; // green
		default:
			color = 0x000000FF;
			break; // blue
		}

		// give x and y sides different brightness
		if (control->side == 1)
		{
			color = color / 2;
		}

		// draw the pixels of the stripe as a vertical line
		verLine(x, drawStart, drawEnd, color, data);
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}

void redraw(t_data *data)
{
	// Put the image to the window
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);

	// Clear the image for the next frame
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	data->img.img = mlx_new_image(data->mlx_ptr, 480, 480);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
}

double getTicks()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
}

void Render(t_data *data, t_dda *control)
{
    control->width = 480;
    control->height = 480;
    int done = 0;
    while (done == 0)
    {

        raycastingLoop(control, data); // calculates and draws vertical lines accordingly

        // timing for input and FPS counter
        data->oldTime = data->time;
        data->time = getTicks();
        data->frameTime = (data->time - data->oldTime) / 1000.0; // frameTime is the time this frame has taken, in seconds

        redraw(data); // here its all drawn, in verLine it should add to buffer and use putimage not putpixel

        // speed modifiers
        data->moveSpeed = data->frameTime * 5.0; // the constant value is in squares/second
        data->rotSpeed = data->frameTime * 3.0;  // the constant value is in radians/second
		done = 1;
    }
}

int loop_handler(t_data *data)
{
    Render(data, &data->control);
    return (0);
}


/**
 * @brief test main
 */
int main(int argc, char **argv)
{
	t_data data;
	int ret;
	int done = 0;
	ret = 0;
	if (parser(argc, argv, &data.map) == -1)
	{
		free_mapS(&data.map);
		return -1;
	}
	setupData(&data);
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 480, 480, "cub3d");
	data.img.img = mlx_new_image(data.mlx_ptr, 480, 480);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, &data.img.line_length, &data.img.endian);

	// square(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 131072, &end_all, &data);
	// Render(&data, &data.control);
    mlx_loop_hook(data.mlx_ptr, loop_handler, &data);

	mlx_loop(data.mlx_ptr);
	end_all(&data);
	return (ret);
}