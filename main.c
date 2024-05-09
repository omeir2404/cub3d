/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 20:07:19 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 20:07:19 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing/parsing.h"
#include "my_mlx/my_mlx.h"
#include <X11/keysym.h>
#include <math.h>
#include <sys/time.h>
#include <X11/Xlib.h>

void	load_image(t_data *data, int texNum, char *path)
{
	int	w;
	int	h;

	w = SCREENWIDTH;
	h = SCREENHEIGHT;
	data->texture[texNum] = (uint32_t *)mlx_xpm_file_to_image(data->mlx_ptr,
			path, &w, &h);
	if (data->texture[texNum] == NULL)
		printf("Error\n");
}

void	get_image_data(t_data *data, int texNum)
{
	int	image_info[3];
	int	bpp;
	int	size;
	int	endian;

	if (data->texture[texNum] != NULL)
		data->adrress[texNum] = (uint32_t *)mlx_get_data_addr(
				data->texture[texNum], &bpp, &size, &endian);
}

void	load_texture(t_data *data, int texNum, char *path)
{
	load_image(data, texNum, path);
	get_image_data(data, texNum);
}

void	file_info(t_data *data)
{
	load_texture(data, NORTH, data->map.north);
	load_texture(data, SOUTH, data->map.south);
	load_texture(data, EAST, data->map.east);
	load_texture(data, WEST, data->map.west);
}

/**
 * @brief test main
 */
int	main(int argc, char **argv)
{
	t_data	data;
	int		ret;
	int		done;

	done = 0;
	ret = 0;
	if (parser(argc, argv, &data.map) == -1)
	{
		free_map_struct(&data.map);
		return (-1);
	}
	setup_data(&data);
	file_info(&data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
	mlx_hook(data.win_ptr, 17, 131072, &end_all, &data);
	mlx_loop_hook(data.mlx_ptr, loop_handler, &data);
	mlx_loop(data.mlx_ptr);
	end_all(&data);
	return (ret);
}