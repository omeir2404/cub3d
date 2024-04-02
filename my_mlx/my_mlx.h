#ifndef MY_MLX_H
#define MY_MLX_H
#include "../parsing/parsing.h"
# include <stdio.h>
# include <string.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <unistd.h>

struct s_data
{
    void		*mlx_ptr;
	void		*win_ptr;
    t_map       map;
};
typedef struct s_data t_data;

int	handle_keypress(int keysym, t_data *data);
int	end_all(t_data *data);
#endif