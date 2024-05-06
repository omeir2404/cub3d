#include "my_mlx.h"

int getDirectionedTexture(t_data *data)
{
	if (data->control.side == 1 && data->control.rayDirY < 0)
		return NORTH;
	else if (data->control.side == 1 && data->control.rayDirY > 0)
		return SOUTH;
	else if (data->control.side == 0 && data->control.rayDirX < 0)
		return EAST;
	else if (data->control.side == 0 && data->control.rayDirX > 0)
		return WEST;
	
	return 0;
}

/**
 * @brief The wall textures for the given x column
 *
 * @param data
 * @param control
 * @param x
 */
void wallTextures(t_data *data, t_dda *control, int x, int texNum)
{
	// int texNum = 3; // choose a number from 0-7 for different textures
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

	// CEILING COLOR
	double texPos = (data->drawStart - pitch - control->height / 2 + data->lineHeight / 2) * step;
	if (data->drawStart > 0 && data->drawStart <= SCREENHEIGHT)
		for (int i = 0; i < data->drawStart; i++)
			data->buffer[i][x] = data->ceilingColor;

	for (int y = data->drawStart; y < data->drawEnd; y++)
	{
		// Cast the texture coordinate to integer, and mask with (texHeight - 1) in case of overflow
		int texY = (int)texPos & (TEXHEIGHT - 1);
		texPos += step;
		uint32_t color = data->adrress[texNum][TEXHEIGHT * texY + texX];
		// uint32_t color = getDirectionedTexture(texX, texY, data);
		// make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
		if (control->side == 1)
			color = (color >> 1) & 8355711;
		data->buffer[y][x] = color;
	}

	// FLOOR COLOR
	if (data->drawEnd > 0 && data->drawEnd <= SCREENHEIGHT)
		for (int i = data->drawEnd; i < SCREENHEIGHT; i++)
			data->buffer[i][x] = data->floorColor;
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
	int texNum = getDirectionedTexture(data);
	wallTextures(data, control, x, texNum);
}

void raycastingLoop(t_dda *control, t_data *data)
{

	for (int x = 0; x < control->width; x++)
	{
		setDdaValues(control, data, x);
		DDA(control, data);
		setDrawingValues(control, data, x);
		// draw the pixels of the stripe as a vertical line
		// verLine(x, data->drawStart, data->drawEnd, data->color, data);
	}
}

void drawBuffer(t_data *data)
{
	// Copy the buffer to the image
	for (int y = 0; y < SCREENHEIGHT; y++)
	{
		for (int x = 0; x < SCREENWIDTH; x++)
		{
			uint32_t color = data->buffer[y][x];
			my_mlx_pixel_put(&data->img, x, y, color);
		}
	}
}

void Render(t_data *data, t_dda *control)
{
	control->height = SCREENHEIGHT;
	control->width = SCREENWIDTH;

	raycastingLoop(control, data); // calculates and draws vertical lines accordingly
	// uncoment if using colors and not textures
	//  mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	drawBuffer(data);
	clearBuffer(data); // try removing this for fun(DON'T!!!)

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
