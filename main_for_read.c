#include "parsing/parsing.h"
#include "my_mlx/my_mlx.h"
#include <X11/keysym.h>
#include <math.h>
#include <sys/time.h>
#include <X11/Xlib.h>

// change to use image textures instead!!!!!
// void generateTextures(t_data *data)
// {
// 	for (int x = 0; x < TEXWIDTH; x++)
// 	{
// 		for (int y = 0; y < TEXHEIGHT; y++)
// 		{
// 			int xorcolor = (x * 256 / TEXWIDTH) ^ (y * 256 / TEXHEIGHT);
// 			int ycolor = y * 256 / TEXHEIGHT;
// 			int xycolor = y * 128 / TEXHEIGHT + x * 128 / TEXWIDTH;
// 			data->texture[0][TEXWIDTH * y + x] = 65536 * 254 * (x != y && x != TEXWIDTH - y);  // flat red data->texture with black cross
// 			data->texture[1][TEXWIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor;	   // sloped greyscale
// 			data->texture[2][TEXWIDTH * y + x] = 256 * xycolor + 65536 * xycolor;			   // sloped yellow gradient
// 			data->texture[3][TEXWIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; // xor greyscale
// 			data->texture[4][TEXWIDTH * y + x] = 256 * xorcolor;							   // xor green
// 			data->texture[5][TEXWIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16);			   // red bricks
// 			data->texture[6][TEXWIDTH * y + x] = 65536 * ycolor;							   // red gradient
// 			data->texture[7][TEXWIDTH * y + x] = 128 + 256 * 128 + 65536 * 128;				   // flat grey texture
// 		}
// 	}
// 	// swap texture X/Y since they'll be used as vertical stripes// TO OPTIMIZE WHENEVER TEXWIDTH == TEXHEIGHT
// 	if (TEXWIDTH == TEXHEIGHT)
// 	{
// 		for (size_t i = 0; i < 8; i++)
// 		{
// 			for (size_t x = 0; x < TEXWIDTH; x++)
// 			{
// 				for (size_t y = 0; y < x; y++)
// 				{
// 					uint32_t temp = data->texture[i][TEXWIDTH * y + x];
// 					data->texture[i][TEXWIDTH * y + x] = data->texture[i][TEXWIDTH * x + y];
// 					data->texture[i][TEXWIDTH * x + y] = temp;
// 				}
// 			}
// 		}
// 	}
// }

void loadTexture(t_data *data, int texNum, char *path)
{
	int i;
	int w;
	int h;

	i = 0;
	h = SCREENHEIGHT;
	w = SCREENWIDTH;

    int bpp, size_line, endian;
    data->texture[texNum] = (uint32_t *)mlx_xpm_file_to_image(data->mlx_ptr, path, &w, &h);
    if (data->texture[texNum]  == NULL) {
        printf("Unable to load image %s!\n", data->map.north);
    } 
	else {
        data->adrress[texNum] = (uint32_t *)mlx_get_data_addr(data->texture[texNum] , &bpp, &size_line, &endian);
    }
}

void fileInfo(t_data *data)
{
	loadTexture(data, NORTH, data->map.north);
	loadTexture(data, SOUTH, data->map.south);
	loadTexture(data, EAST, data->map.east);
	loadTexture(data, WEST, data->map.west);

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
	// printf("floor: %s", data.map.floor);
	// printf("ceiling: %s", data.map.ceiling);

	setupData(&data);
	fileInfo(&data);
	// generateTextures(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 131072, &end_all, &data);
	mlx_loop_hook(data.mlx_ptr, loop_handler, &data);
	mlx_loop(data.mlx_ptr);
	end_all(&data);
	return (ret);
}