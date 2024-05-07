/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_press.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:57:12 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 18:12:00 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_mlx.h"
#include "../parsing/parsing.h"
#include <math.h>

void	handle_left(t_data *data)
{
	printf("move left\n");
	if (data->map.map[(int)(data->pos_y - data->plane_y * data->move_speed)]
		[(int)(data->pos_x)] != '1')
		data->pos_y -= data->plane_y * data->move_speed;
	if (data->map.map[(int)(data->pos_y)][(int)(data->pos_x - data->plane_x
		* data->move_speed)] != '1')
		data->pos_x -= data->plane_x * data->move_speed;
}

void	look_right(t_data *data, double olddir_y, double oldplane_y)
{
	printf("look right\n");
	olddir_y = data->dir_y;
	data->dir_y = data->dir_y * cos(-data->rot_speed) - data->dir_x
		* sin(-data->rot_speed);
	data->dir_x = olddir_y * sin(-data->rot_speed) + data->dir_x
		* cos(-data->rot_speed);
	oldplane_y = data->plane_y;
	data->plane_y = data->plane_y * cos(-data->rot_speed) - data->plane_x
		* sin(-data->rot_speed);
	data->plane_x = oldplane_y * sin(-data->rot_speed) + data->plane_x
		* cos(-data->rot_speed);
}

void	look_left(t_data *data, double olddir_y, double oldplane_y)
{
	printf("look left\n");
	olddir_y = data->dir_y;
	data->dir_y = data->dir_y * cos(data->rot_speed) - data->dir_x
		* sin(data->rot_speed);
	data->dir_x = olddir_y * sin(data->rot_speed) + data->dir_x
		* cos(data->rot_speed);
	oldplane_y = data->plane_y;
	data->plane_y = data->plane_y * cos(data->rot_speed) - data->plane_x
		* sin(data->rot_speed);
	data->plane_x = oldplane_y * sin(data->rot_speed) + data->plane_x
		* cos(data->rot_speed);
}

int	handle_keypress(int keycode, t_data *data)
{
	double	olddir_y;
	double	oldplane_y;

	olddir_y = 0;
	oldplane_y = 0;
	if (keycode == XK_Up || keycode == XK_w)
		handle_forward(data);
	else if (keycode == XK_Down || keycode == XK_s)
		handle_backward(data);
	else if (keycode == XK_d)
		handle_right(data);
	else if (keycode == XK_a)
		handle_left(data);
	else if (keycode == XK_Right)
		look_right(data, olddir_y, oldplane_y);
	else if (keycode == XK_Left)
		look_left(data, olddir_y, oldplane_y);
	else if (keycode == XK_Escape)
		end_all(data);
	return (0);
}

int	end_all(t_data *data)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (data->texture[i])
			mlx_destroy_image(data->mlx_ptr, (void *)data->texture[i]);
		i++;
	}
	if (data && data->mlx_ptr && data->win_ptr)
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	if (data->img.img)
		mlx_destroy_image(data->mlx_ptr, data->img.img);
	if (data->mlx_ptr)
	{
		mlx_destroy_display(data->mlx_ptr);
		free(data->mlx_ptr);
	}
	free_map_struct(&data->map);
	exit(0);
}
