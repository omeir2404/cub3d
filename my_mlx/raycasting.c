#include "my_mlx.h"

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
	for (int i = 0; i < 8; i++)
		data->texture[i] = (uint32_t *)malloc(TEXWIDTH * TEXHEIGHT * sizeof(uint32_t));
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

void wallTextures(t_data *data, t_dda *control, int x)
{
	int texNum = 3;//choose a number from 0-7 for different textures 
	// texturing calculations
	// if (data->map.map[control->mapX][control->mapY] == '1')
	// 	int texNum =ft_atoi(data->map.map[control->mapX][control->mapY]) - 1; // 1 subtracted from it so that texture 0 can be used!

	// calculate value of wallX
	double wallX; // where exactly the wall was hit
	if (control->side == 0)
		wallX = data->posY + control->perpWallDist * control->rayDirY;
	else
		wallX = data->posX + control->perpWallDist * control->rayDirX;
	wallX -= floor((wallX));

	// x coordinate on the texture
	int texX = (int)(wallX * (double)TEXWIDTH);
	if (control->side == 0 && control->rayDirX > 0)
		texX = TEXWIDTH - texX - 1;
	if (control->side == 1 && control->rayDirY < 0)
		texX = TEXWIDTH - texX - 1;
	int pitch = 100; // check what this is for
	// TODO: an integer-only bresenham or DDA like algorithm could make the texture coordinate stepping faster
	// How much to increase the texture coordinate per screen pixel
	double step = 1.0 * TEXHEIGHT / data->lineHeight;
	// Starting texture coordinate
	double texPos = (data->drawStart - pitch - control->height / 2 + data->lineHeight / 2) * step;
	for (int y = data->drawStart; y < data->drawEnd; y++)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (TEXHEIGHT - 1);
		texPos += step;
		// uint32_t color = data->texture[texNum][TEXHEIGHT * texY + texX];
		uint32_t color = data->texture[texNum][TEXHEIGHT * texX + texY];
		// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if (control->side == 1)
			color = (color >> 1) & 8355711;
		data->buffer[y][x] = color;
	}
}

void setDrawingValues(t_dda *control, t_data *data, int x)
{
	// Calculate distance projected on camera direction (Euclidean distance would give fisheye effect!)
	if (control->side == 0)
		control->perpWallDist = (control->sideDistX - control->deltaDistX);
	else
		control->perpWallDist = (control->sideDistY - control->deltaDistY);

	// Calculate height of line to draw on screen
	data->lineHeight = (int)(control->height / control->perpWallDist);

	// calculate lowest and highest pixel to fill in current stripe
	data->drawStart = -data->lineHeight / 2 + control->height / 2;
	if (data->drawStart < 0)
		data->drawStart = 0;
	data->drawEnd = data->lineHeight / 2 + control->height / 2;
	if (data->drawEnd >= control->height)
		data->drawEnd = control->height - 1;
	// wallColors(data, control);
	wallTextures(data, control, x);
}

void raycastingLoop(t_dda *control, t_data *data)
{

	for (int x = 0; x < control->width; x++)
	{
		setDdaValues(control, data, x);
		DDA(control, data);
		setDrawingValues(control, data, x);
		// draw the pixels of the stripe as a vertical line
		verLine(x, data->drawStart, data->drawEnd, data->color, data);
	}
}

void redraw(t_data *data)
{
	// Put the image to the window
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);

	// Clear the image(buffer) for the next frame
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	data->img.img = mlx_new_image(data->mlx_ptr, SCREENWIDTH, SCREENHEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
}

double getTicks()
{
	struct timeval tv;
	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
}

void drawBuffer(t_data *data)
{
    // Create a new image
    // t_img img;
    // img.img = mlx_new_image(data->mlx_ptr, SCREENWIDTH, SCREENHEIGHT);
    // img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);

    // Copy the buffer to the image
    for (int y = 0; y < SCREENHEIGHT; y++)
    {
        for (int x = 0; x < SCREENWIDTH; x++)
        {
            uint32_t color = data->buffer[y][x];
            my_mlx_pixel_put(&data->img, x, y, color);
        }
    }

    // Draw the image to the window
    mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
}
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

void Render(t_data *data, t_dda *control)
{
	control->width = 640;
	control->height = 480;

	raycastingLoop(control, data); // calculates and draws vertical lines accordingly
	//uncoment if using colors and not textures
	// mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	drawBuffer(data);
	clearBuffer(data);//try removing this for fun(DON'T!!!)

	// timing for input and FPS counter
	data->oldTime = data->time;
	data->time = getTicks();
	data->frameTime = (data->time - data->oldTime) / 1000.0; // frameTime is the time this frame has taken, in seconds
	// printf("%f\n", 1.0 / data->frameTime);
	redraw(data); // here its all drawn, in verLine it should add to buffer and use putimage not putpixel

	// speed modifiers
	data->moveSpeed = data->frameTime * 5.0; // the constant value is in squares/second
	data->rotSpeed = data->frameTime * 3.0;	 // the constant value is in radians/second
}

int loop_handler(t_data *data)
{
	Render(data, &data->control);
	return (0);
}
