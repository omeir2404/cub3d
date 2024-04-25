#include "my_mlx.h"
#include "../parsing/parsing.h"


int	handle_keypress2(int keysym, t_data *data)
{
	if (keysym == 0xff52 || keysym == 0x77)// up or w
        printf("right move\n");
	if (keysym == 0xff53 || keysym == 0x64) // right or d
        printf("right move\n");
	return (0);
}

int	handle_keypress(int keysym, t_data *data)
{
	if (keysym == 0xff1b)//escape
		end_all(data);
	if (keysym == 0xff52 || keysym == 0x77)
		handle_keypress2(keysym, data);
	if (keysym == 0xff53 || keysym == 0x64)
		handle_keypress2(keysym, data);
	if (keysym == 0xff51 || keysym == 0x61) //left or a
        printf("right move\n");
	if (keysym == 0xff54 || keysym == 0x73)// down or s
        printf("right move\n");
	return (0);
}


int	end_all(t_data *data)
{
	free_mapS(&data->map);
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	// if (data->mlx_ptr)
	// 	free(data->mlx_ptr);
	// mlx_destroy_display(data->mlx_ptr);
	return (0);
}