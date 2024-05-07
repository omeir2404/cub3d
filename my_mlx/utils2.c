/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:28:56 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 19:31:41 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_mlx.h"

void	fill_buffer(t_data *data, uint32_t color,
	uint32_t buffer[][SCREENWIDTH], int x)
{
	int	i;

	i = 0;
	while (i < data->draw_start)
	{
		buffer[i][x] = color;
		i++;
	}
}

void	fill_buffer2(t_data *data, uint32_t color,
	uint32_t buffer[][SCREENWIDTH], int x)
{
	int	i;

	i = data->draw_end;
	while (i < SCREENHEIGHT)
	{
		buffer[i][x] = color;
		i++;
	}
}

void	calculate_wall_x(t_data *data, t_dda *control)
{
	if (control->side == 0)
		data->wall_x = data->pos_y + control->perp_wall_dist
			* control->ray_dir_y;
	else
		data->wall_x = data->pos_x + control->perp_wall_dist
			* control->ray_dir_x;
	data->wall_x -= floor((data->wall_x));
}

void	calculate_tex_x(t_data *data, t_dda *control, int *tex_x)
{
	*tex_x = (int)(data->wall_x * (double)TEXWIDTH);
	if ((control->side == 0 && control->ray_dir_x > 0)
		|| (control->side == 1 && control->ray_dir_y < 0))
		*tex_x = TEXWIDTH - *tex_x - 1;
}

void	calculate_tex_pos(t_data *data, t_dda *control, double *tex_pos)
{
	data->step = 1.0 * TEXHEIGHT / data->line_height;
	*tex_pos = (data->draw_start - control->height / 2
			+ data->line_height / 2) * data->step;
}
