#include "parsing/parsing.h"
#include "my_mlx/my_mlx.h"
#include <X11/keysym.h>
#include <math.h>
#include <sys/time.h>
#include <X11/Xlib.h>

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

	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 131072, &end_all, &data);
    mlx_loop_hook(data.mlx_ptr, loop_handler, &data);
	mlx_loop(data.mlx_ptr);
	end_all(&data);
	return (ret);
}