#include "parsing/parsing.h"
#include "my_mlx/my_mlx.h"
#include <X11/keysym.h>
#include <math.h>
#include <sys/time.h>
#include <X11/Xlib.h>


//change to use image textures instead!!!!!
void generateTextures(t_data *data)
{
	for (int x = 0; x < TEXWIDTH; x++)
	{
		for (int y = 0; y < TEXHEIGHT; y++)
		{
			int xorcolor = (x * 256 / TEXWIDTH) ^ (y * 256 / TEXHEIGHT);
			int ycolor = y * 256 / TEXHEIGHT;
			int xycolor = y * 128 / TEXHEIGHT + x * 128 / TEXWIDTH;
			data->texture[0][TEXWIDTH * y + x] = 65536 * 254 * (x != y && x != TEXWIDTH - y);	 // flat red data->texture with black cross
			data->texture[1][TEXWIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;	 // sloped greyscale
			data->texture[2][TEXWIDTH * y + x] = 256 * xycolor + 65536 * xycolor;				 // sloped yellow gradient
			data->texture[3][TEXWIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; // xor greyscale
			data->texture[4][TEXWIDTH * y + x] = 256 * xorcolor;								 // xor green
			data->texture[5][TEXWIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16);			 // red bricks
			data->texture[6][TEXWIDTH * y + x] = 65536 * ycolor;								 // red gradient
			data->texture[7][TEXWIDTH * y + x] = 128 + 256 * 128 + 65536 * 128;				 // flat grey texture
		}
	}
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
	generateTextures(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 131072, &end_all, &data);
	mlx_loop_hook(data.mlx_ptr, loop_handler, &data);
	mlx_loop(data.mlx_ptr);
	end_all(&data);
	return (ret);
}