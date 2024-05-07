/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 12:53:56 by oharoon           #+#    #+#             */
/*   Updated: 2024/05/07 12:53:56 by oharoon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "../libft/libft.h"
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../minilibx-linux/mlx.h"

// #define malloc(x) 0 // TESTAR PARA TODOS OS MALLOCS SEREM NULOS

struct s_map
{
	char	**map;
	char	*north;
	char	*west;
	char	*east;
	char	*south;
	char	*floor;
	char	*ceiling;
	int		fd;
	char	*file;
	int		found_direction;
	char	direction;
	int		found_player;
	int		player_pos[2];
	int		longest_line;
	int		map_size;
};
typedef struct s_map		t_map;

struct	s_indices
{
	int	i;
	int	lol;
};
typedef struct s_indices	t_indices;

void	free_mat(char **matrix);
int		check_args(int argc, char **argv);
int		info_parse(t_map *map);
int		check_file_access(char *file);
int		parse_map(char **map, t_map *struc);
int		get_map_size(int *fd, t_map *map);
char	**copy_mat(t_map *map);
int		map_start(char *s);
int		open_file(t_map *map);
int		collected_info(t_map map);
int		get_info(t_map *map);
void	show_map_info(t_map map);
void	free_map_struct(t_map *map);
int		allocate_map(t_map *map);
void	get_direction(char *s, char **direction);
int		parser(int argc, char **argv, t_map *map);
int		check_valid_char(char c);
int		last_in_line(char *line, int index);
int		check_map_chars(char **map, t_map *struc);
int		is_quad(char **map);
int		map_quad(t_map *map);
void	struct_init(t_map *map, char **argv);
int		map_init(t_map *map);

#endif