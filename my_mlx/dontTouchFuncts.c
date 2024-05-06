#include "my_mlx.h"

/**
 * @brief Get the Ticks object(for frame rate)
 * 
 * @return double 
 */
double getTicks()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
}

/**
 * @brief solid color walls and not textures, NOT NEEDED
 * 
 * @param data 
 * @param control 
 */
void wallColors(t_data *data, t_dda *control)
{
	// choose wall color
	if (data->map.map[control->mapY][control->mapX] == '1')
	{
		data->color = 0x00FFA500; // orange

		if (fabs(data->dirX) < 1e-6 && data->dirY < -0.5)
		{
			if (control->side == 0)
				data->color = 0x000000FF; // blue
										  // else
										  // 	data->color = 0x0000FF00; // green
		}
		else if (fabs(data->dirX) < 1e-6 && data->dirY > 0.5) // 1e-6 e um num muito pequeno em vez de usar 0
		{
			if (control->side == 0)
				data->color = 0x00FFFF00; // yellow
										  // else
										  // 	data->color = 0x0000FF00; // green
		}
		else if (data->dirX > 0.5 && fabs(data->dirY) < 1e-6)
		{
			if (control->side == 0)
				data->color = 0x00FF00FF; // magenta
										  // else
										  // 	data->color = 0x0000FF00; // green
		}
		else if (data->dirX < -0.5 && fabs(data->dirY) < 1e-6)
		{
			if (control->side == 0)
				data->color = 0x00FF0000; // red

			// else
			// 	data->color = 0x0000FF00; // green
		}
	}

	// give x and y sides different brightness
	if (control->side == 1)
		data->color = data->color / 2;
}

/**
 * @brief draw a vertical line onto the buffer(with solid colors) NOT NEEDED
 * 
 * @param x 
 * @param start 
 * @param end 
 * @param color 
 * @param data 
 */
void verLine(int x, int start, int end, int color, t_data *data)
{
	printf("start value: %d\n", start);
	for (int i = 0; i < start; i++)
		my_mlx_pixel_put(&data->img, x, i, data->ceilingColor);
	for (int y = start; y < end; y++)
		my_mlx_pixel_put(&data->img, x, y, color);
	for (int i = end; i < SCREENHEIGHT; i++)
		my_mlx_pixel_put(&data->img, x, i, data->floorColor);
}



/**
 * @brief Set the DDA variables
 * 
 * @param control 
 * @param data 
 * @param x 
 */
void setDdaValues(t_dda *control, t_data *data, int x)
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
}

/**
 * @brief DDA ALGORITHM
 * 
 * @param control 
 * @param data 
 */
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

/**
 * @brief purs a pixel of colir into the image adress
 * 
 * @param img 
 * @param x 
 * @param y 
 * @param color 
 */
void my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char *dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief initial variables for the data structure
 * 
 * @param data 
 */
void setupData(t_data *data)
{
	// for (int i = 0; i < 4; i++)
	// 	data->texture[i] = NULL;
		// data->texture[i] = (uint32_t *)malloc(TEXWIDTH * TEXHEIGHT * sizeof(uint32_t));
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREENWIDTH, SCREENHEIGHT, "cub3d");
	data->img.img = mlx_new_image(data->mlx_ptr, SCREENWIDTH, SCREENHEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);

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
	data->drawStart = 0;
	data->drawEnd = 0;

	data->ceilingColor = getColors(data->map.ceiling);
	data->floorColor = getColors(data->map.floor);
	// data->ceilingColor = 0xA3CEEF; // blue
	// data->floorColor = 0xFC6998; // pink

	setupControl(&data->control);
}

/**
 * @brief Get the Colors objectget hex colors from rgb char formar (ex: "255,43,234")
 * 
 * @param rgb 
 * @return int 
 */
int getColors(char *rgb)
{
	char **split = ft_split(rgb, ',');
	int r = atoi(split[0]);
	int g = atoi(split[1]);
	int b = atoi(split[2]);

	int hexColor = (r << 16) | (g << 8) | b;
	for (int i = 0; i < 3; i++)
		free(split[i]);
	free(split);
	return hexColor;
}
/**
 * @brief initial variables for the control structure
 * 
 * @param control 
 */
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

/**
 * @brief clears the data buffer used for the textured image
 * 
 */
void clearBuffer(t_data *data)
{
	for (int y = 0; y < SCREENHEIGHT; y++)
	{
		for (int x = 0; x < SCREENWIDTH; x++)
		{
			data->buffer[y][x] = 0;
		}
	}
}

/**
 * @brief basicallyb keeps the image on the window 
 * 
 * @param data 
 */
void redraw(t_data *data)
{
	// Put the image to the window
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);

	// Clear the image(buffer) for the next frame
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	data->img.img = mlx_new_image(data->mlx_ptr, SCREENWIDTH, SCREENHEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
}