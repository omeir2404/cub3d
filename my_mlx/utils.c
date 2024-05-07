/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:11:13 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 18:11:55 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_mlx.h"

void	handle_forward(t_data *data)
{
	printf("forward\n");
	if (data->map.map[(int)(data->pos_y + data->dir_y * data->move_speed)]
		[(int)(data->pos_x)] != '1')
		data->pos_y += data->dir_y * data->move_speed;
	if (data->map.map[(int)(data->pos_y)][(int)(data->pos_x + data->dir_x
		* data->move_speed)] != '1')
		data->pos_x += data->dir_x * data->move_speed;
}

void	handle_backward(t_data *data)
{
	printf("backwards\n");
	if (data->map.map[(int)(data->pos_y - data->dir_y * data->move_speed)]
		[(int)(data->pos_x)] != '1')
		data->pos_y -= data->dir_y * data->move_speed;
	if (data->map.map[(int)(data->pos_y)][(int)(data->pos_x - data->dir_x
		* data->move_speed)] != '1')
		data->pos_x -= data->dir_x * data->move_speed;
}

void	handle_right(t_data *data)
{
	printf("move right\n");
	if (data->map.map[(int)(data->pos_y + data->plane_y * data->move_speed)]
		[(int)(data->pos_x)] != '1')
		data->pos_y += data->plane_y * data->move_speed;
	if (data->map.map[(int)(data->pos_y)][(int)(data->pos_x + data->plane_x
		* data->move_speed)] != '1')
		data->pos_x += data->plane_x * data->move_speed;
}
