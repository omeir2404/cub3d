/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:51:46 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 19:52:46 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_mlx.h"

/**
 * @brief initial variables for the control structure
 * 
 * @param control 
 */
void	setup_control(t_dda *control)
{
	control->width = 0;
	control->height = 0;
	control->camera_x = 0;
	control->ray_dir_x = 0;
	control->ray_dir_y = 0;
	control->map_y = 0;
	control->map_x = 0;
	control->side_dist_x = 0;
	control->side_dist_y = 0;
	control->delta_dist_x = 0;
	control->delta_dist_y = 0;
	control->perp_wall_dist = 0;
	control->step_x = 0;
	control->step_y = 0;
	control->hit = 0;
	control->side = 0;
}

/**
 * @brief clears the data buffer used for the textured image
 * 
 */
void	clear_buffer(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			data->buffer[y][x] = 0;
			x++;
		}
		y++;
	}
}

/**
 * @brief basicallyb keeps the image on the window 
 * 
 * @param data 
 */
void	redraw(t_data *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	data->img.img = mlx_new_image(data->mlx_ptr, SCREENWIDTH, SCREENHEIGHT);
	data->img.addr = mlx_get_data_addr(data->img.img, \
		&data->img.bits_per_pixel, &data->img.line_length, &data->img.endian);
}
