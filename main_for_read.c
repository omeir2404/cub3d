#include "parsing/parsing.h"
#include "my_mlx/my_mlx.h"
# include <X11/keysym.h>
// struct s_data
// {
//     void		*mlx_ptr;
// 	void		*win_ptr;
// };
// typedef struct s_data t_data;

// int	handle_keypress(int keysym, t_data *data);
// int	end_all(t_data *data, t_map *map);
/**
 * @brief test main 
*/
int main(int argc, char **argv)
{
	// t_map map;
	t_data data;
	int ret;
	// void	*mlx;
	// void	*mlx_win;

	ret = 0;
	if(parser(argc, argv, &data.map) == -1)
		return -1;
	data.mlx_ptr = mlx_init();
	data.win_ptr = mlx_new_window(data.mlx_ptr, 480, 480, "Hello world!");
	mlx_hook(data.win_ptr, handle_keypress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 131072, &end_all, &data);
	mlx_loop(data.mlx_ptr);
	end_all(&data, &data.map);
	// free_mapS(&map);
	return (ret);
}