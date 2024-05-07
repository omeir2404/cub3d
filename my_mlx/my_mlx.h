/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   my_mlx.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 17:00:55 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 19:49:09 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MY_MLX_H
# define MY_MLX_H
# include "../parsing/parsing.h"
# include <stdio.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

# include <math.h>
# include <stdint.h>
# include <sys/time.h>
# include <X11/Xlib.h>

# define SCREENWIDTH 1080
# define SCREENHEIGHT 500
# define TEXHEIGHT 64
# define TEXWIDTH 64
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}			t_img;

struct s_dda
{
	int		width;
	int		height;

	double	camera_x;
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_y;
	int		map_x;

	double	side_dist_x;
	double	side_dist_y;

	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	int		step_x;
	int		step_y;

	int		hit;

	int		side;
};
typedef struct s_dda	t_dda;

struct s_data
{
	void		*mlx_ptr;
	void		*win_ptr;

	int			floor_color;
	int			ceiling_color;

	double		pos_x;
	double		pos_y; // x and y start position
	double		dir_x;
	double		dir_y; // initial direction vector
	double		plane_x;
	double		plane_y; // the 2d raycaster version of camera plane
	double		time; // time of current frame
	double		old_time; // time of previous frame
	double		frame_time;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			color;

	double		wall_x;
	double		step;

	double		move_speed;
	double		rot_speed;

	uint32_t	buffer[SCREENHEIGHT][SCREENWIDTH];
	uint32_t	*texture[4];
	uint32_t	*adrress[4];

	t_dda		control;
	t_img		img;
	t_map		map;
};
typedef struct s_data	t_data;

void	render(t_data *data, t_dda *control);
int		handle_keypress(int keysym, t_data *data);
int		end_all(t_data *data);
int		loop_handler(t_data *data);
void	handle_forward(t_data *data);
void	handle_backward(t_data *data);
void	handle_right(t_data *data);

double	get_ticks(void);
void	wall_colors(t_data *data, t_dda *control);
void	set_dda_values(t_dda *control, t_data *data, int x);
void	dda(t_dda *control, t_data *data);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);
void	setup_data(t_data *data);
int		get_colors(char *rgb);
void	setup_control(t_dda *control);
void	clear_buffer(t_data *data);
void	redraw(t_data *data);

int		get_directioned_texture(t_data *data);
void	fill_buffer(t_data *data, uint32_t color,
			uint32_t buffer[][SCREENWIDTH], int x);
void	fill_buffer2(t_data *data, uint32_t color,
			uint32_t buffer[][SCREENWIDTH], int x);
void	calculate_wall_x(t_data *data, t_dda *control);
void	calculate_tex_x(t_data *data, t_dda *control, int *tex_x);
void	calculate_tex_pos(t_data *data, t_dda *control, double *tex_pos);

#endif