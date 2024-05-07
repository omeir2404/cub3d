/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dontTouchFuncts.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:33:42 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 19:47:20 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_mlx.h"

/**
 * @brief Get the Ticks object(for frame rate)
 * 
 * @return double 
 */
double	get_ticks(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000.0 + tv.tv_usec / 1000.0);
}

/**
 * @brief solid color walls and not textures, NOT NEEDED
 * @param data 
 * @param control 
 */
void	wall_colors(t_data *data, t_dda *control)
{
	if (data->map.map[control->map_y][control->map_x] == '1')
	{
		data->color = 0x00FFA500;
		if (fabs(data->dir_x) < 1e-6 && data->dir_y < -0.5)
			if (control->side == 0)
				data->color = 0x000000FF;
		else if (fabs(data->dir_x) < 1e-6 && data->dir_y > 0.5)
			if (control->side == 0)
				data->color = 0x00FFFF00;
		else if (data->dir_x > 0.5 && fabs(data->dir_y) < 1e-6)
			if (control->side == 0)
				data->color = 0x00FF00FF;
		else if (data->dir_x < -0.5 && fabs(data->dir_y) < 1e-6)
			if (control->side == 0)
				data->color = 0x00FF0000;
	}
	if (control->side == 1)
		data->color = data->color / 2;
}
