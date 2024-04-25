#include "parsing/parsing.h"
#include "my_mlx/my_mlx.h"
#include <X11/keysym.h>

void square(t_data *data)
{
	for (int i = 100; i < 200; i++)
		for (int j = 100; j < 200; j++)
			mlx_pixel_put(data->mlx_ptr, data->win_ptr, i, j, 0x00FF0000);
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
}

void render(t_data *data)
{
	int width = 480;
	int done = 0;
	while (done == 0)
	{
		for (int x = 0; x < width; x++)
		{
			for (int x = 0; x < width; x++)
			{
				double cameraX = 2 * x / (double)width - 1; // x-coordinate in camera space
				double rayDirX = data->dirX + data->planeX * cameraX;
				double rayDirY = data->dirY + data->planeY * cameraX;
			}

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
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 480, 480, "Hello world!");
	// square(&data);
	render(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 131072, &end_all, &data);
	mlx_loop(data.mlx_ptr);
	end_all(&data);
	return (ret);
}