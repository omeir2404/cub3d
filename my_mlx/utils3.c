/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 19:32:02 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 19:33:14 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "my_mlx.h"

int	get_directioned_texture(t_data *data)
{
	if (data->control.side == 1 && data->control.ray_dir_y < 0)
		return (NORTH);
	else if (data->control.side == 1 && data->control.ray_dir_y > 0)
		return (SOUTH);
	else if (data->control.side == 0 && data->control.ray_dir_x < 0)
		return (EAST);
	else if (data->control.side == 0 && data->control.ray_dir_x > 0)
		return (WEST);
	return (0);
}

int	loop_handler(t_data *data)
{
	render(data, &data->control);
	return (0);
}
