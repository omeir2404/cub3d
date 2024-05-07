/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:12:20 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 19:32:55 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_mlx.h"

/**
 * @brief The wall textures for the given x column
 *
 * @param data
 * @param control
 * @param x
 */
void	wall_textures(t_data *data, t_dda *control, int x, int tex_num)
{
	double		tex_pos;
	int			tex_x;
	int			y;
	int			tex_y;
	uint32_t	color;

	calculate_wall_x(data, control);
	calculate_tex_x(data, control, &tex_x);
	calculate_tex_pos(data, control, &tex_pos);
	if (data->draw_start > 0 && data->draw_start <= SCREENHEIGHT)
		fill_buffer(data, data->ceiling_color, data->buffer, x);
	y = data->draw_start;
	while (y < data->draw_end)
	{
		tex_y = (int)tex_pos & (TEXHEIGHT - 1);
		tex_pos += data->step;
		color = data->adrress[tex_num][TEXHEIGHT * tex_y + tex_x];
		if (control->side == 1)
			color = (color >> 1) & 8355711;
		data->buffer[y][x] = color;
		y++;
	}
	if (data->draw_end > 0 && data->draw_end <= SCREENHEIGHT)
		fill_buffer2(data, data->floor_color, data->buffer, x);
}

void	set_drawing_values(t_dda *control, t_data *data, int x)
{
	int	tex_num;

	if (control->side == 0)
		control->perp_wall_dist = (control->side_dist_x
				- control->delta_dist_x);
	else
		control->perp_wall_dist = (control->side_dist_y
				- control->delta_dist_y);
	data->line_height = (int)(control->height / control->perp_wall_dist);
	data->draw_start = -data->line_height / 2 + control->height / 2;
	if (data->draw_start < 0)
		data->draw_start = 0;
	data->draw_end = data->line_height / 2 + control->height / 2;
	if (data->draw_end >= control->height)
		data->draw_end = control->height - 1;
	tex_num = get_directioned_texture(data);
	wall_textures(data, control, x, tex_num);
}

void	raycasting_loop(t_dda *control, t_data *data)
{
	int	x;

	x = 0;
	while (x < control->width)
	{
		set_dda_values(control, data, x);
		dda(control, data);
		set_drawing_values(control, data, x);
		x++;
	}
}

void	draw_buffer(t_data *data)
{
	int			y;
	int			x;
	uint32_t	color;

	y = 0;
	while (y < SCREENHEIGHT)
	{
		x = 0;
		while (x < SCREENWIDTH)
		{
			color = data->buffer[y][x];
			my_mlx_pixel_put(&data->img, x, y, color);
			x++;
		}
		y++;
	}
}

void	render(t_data *data, t_dda *control)
{
	control->height = SCREENHEIGHT;
	control->width = SCREENWIDTH;
	raycasting_loop(control, data);
	draw_buffer(data);
	clear_buffer(data);
	data->old_time = data->time;
	data->time = get_ticks();
	data->frame_time = (data->time - data->old_time) / 1000.0;
	redraw(data);
	data->move_speed = data->frame_time * 2.0;
	data->rot_speed = data->frame_time * 1.0;
}
