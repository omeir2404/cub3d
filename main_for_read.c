#include "parsing/parsing.h"
#include "my_mlx/my_mlx.h"
# include <X11/keysym.h>
/**
 * @brief test main 
*/
int main(int argc, char **argv)
{
	t_data data;
	int ret;

	ret = 0;
	if(parser(argc, argv, &data.map) == -1)
	{
		free_mapS(&data.map);
		return -1;
	}
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 480, 480, "Hello world!");
	for(int i = 100; i < 200; i++)
		for (int j = 100; j < 200; j++)
			mlx_pixel_put(data.mlx_ptr, data.win_ptr, i,j, 0x00FF0000);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 131072, &end_all, &data);
	mlx_loop(data.mlx_ptr);
	end_all(&data);
	return (ret);
}