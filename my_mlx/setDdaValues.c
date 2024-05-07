/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setDdaValues.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:46:57 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 19:55:43 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_mlx.h"

void	set_camera_and_ray_direction(t_dda *control, t_data *data, int x)
{
	control->camera_x = 2 * x / (double)control->width - 1;
	control->ray_dir_x = data->dir_x + data->plane_x * control->camera_x;
	control->ray_dir_y = data->dir_y + data->plane_y * control->camera_x;
}

void	set_map_and_delta_dist(t_dda *control, t_data *data)
{
	control->map_y = (int)data->pos_y;
	control->map_x = (int)data->pos_x;
	if (control->ray_dir_x == 0)
		control->delta_dist_x = 1e30;
	else
		control->delta_dist_x = fabs(1 / control->ray_dir_x);
	if (control->ray_dir_y == 0)
		control->delta_dist_y = 1e30;
	else
		control->delta_dist_y = fabs(1 / control->ray_dir_y);
}

void	set_step_and_side_dist(t_dda *control, t_data *data)
{
	if (control->ray_dir_x < 0)
	{
		control->step_x = -1;
		control->side_dist_x = (data->pos_x - control->map_x)
			* control->delta_dist_x;
	}
	else
	{
		control->step_x = 1;
		control->side_dist_x = (control->map_x + 1.0 - data->pos_x)
			* control->delta_dist_x;
	}
	if (control->ray_dir_y < 0)
	{
		control->step_y = -1;
		control->side_dist_y = (data->pos_y - control->map_y)
			* control->delta_dist_y;
	}
	else
	{
		control->step_y = 1;
		control->side_dist_y = (control->map_y + 1.0 - data->pos_y)
			* control->delta_dist_y;
	}
}

/**
 * @brief Set the dda variables
 * 
 * @param control 
 * @param data 
 * @param x 
 */

void	set_dda_values(t_dda *control, t_data *data, int x)
{
	set_camera_and_ray_direction(control, data, x);
	set_map_and_delta_dist(control, data);
	control->hit = 0;
	set_step_and_side_dist(control, data);
}

/**
 * @brief Get the Colors objectget hex colors
 * from rgb char format (ex: "255,43,234")
 * 
 * @param rgb 
 * @return int 
 */
int	get_colors(char *rgb)
{
	char	**split;
	int		r;
	int		g;
	int		b;
	int		i;

	split = ft_split(rgb, ',');
	r = atoi(split[0]);
	g = atoi(split[1]);
	b = atoi(split[2]);
	i = 0;
	while (i < 3)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return ((r << 16) | (g << 8) | b);
}
