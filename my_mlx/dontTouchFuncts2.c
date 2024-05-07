/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dontTouchFuncts2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:45:26 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 19:56:22 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_mlx.h"

/**
 * @brief dda ALGORITHM
 * 
 * @param control 
 * @param data 
 */
void	dda(t_dda *control, t_data *data)
{
	while (control->hit == 0)
	{
		if (control->side_dist_x < control->side_dist_y)
		{
			control->side_dist_x += control->delta_dist_x;
			control->map_x += control->step_x;
			control->side = 0;
		}
		else
		{
			control->side_dist_y += control->delta_dist_y;
			control->map_y += control->step_y;
			control->side = 1;
		}
		if ((data->map.map[control->map_y][control->map_x]) == '1')
			control->hit = 1;
	}
}

/**
 * @brief purs a pixel of colir into the image adress
 * 
 * @param img 
 * @param x 
 * @param y 
 * @param color 
 */
void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief initial variables for the data structure
 * 
 * @param data 
 */
void	setup_graphics(t_data *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, SCREENWIDTH,
			SCREENHEIGHT, "cub3d");
	data->img.img = mlx_new_image(data->mlx_ptr, SCREENWIDTH, SCREENHEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel, &data->img.line_length,
			&data->img.endian);
}

void	setup_position_and_direction(t_data *data)
{
	data->pos_x = data->map.player_pos[0];
	data->pos_y = data->map.player_pos[1];
	if (data->map.direction == 'N')
	{
		data->dir_x = 0;
		data->dir_y = -1;
	}
	else if (data->map.direction == 'S')
	{
		data->dir_x = 0;
		data->dir_y = 1;
	}
	else if (data->map.direction == 'E')
	{
		data->dir_x = 1;
		data->dir_y = 0;
	}
	else if (data->map.direction == 'W')
	{
		data->dir_x = -1;
		data->dir_y = 0;
	}
}

void	setup_data(t_data *data)
{
	setup_graphics(data);
	setup_position_and_direction(data);
	data->draw_start = 0;
	data->draw_end = 0;
	data->ceiling_color = get_colors(data->map.ceiling);
	data->floor_color = get_colors(data->map.floor);
	setup_control(&data->control);
	data->plane_x = data->dir_y;
	data->plane_x = -data->dir_y;
	data->plane_y = data->dir_x;
	data->time = 0;
	data->old_time = 0;
}
