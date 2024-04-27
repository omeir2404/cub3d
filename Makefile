NAME = 		cub3D
SRC =       parsing/arg_check.c main_for_read.c parsing/map_parse.c \
			parsing/info_parse.c parsing/working_utils.c parsing/parser.c \
			my_mlx/key_press.c my_mlx/raytracing.c
LIBFT_DIR	= libft 
LIBFT		= libft/libft.a
MLX_DIR		= ./minilibx-linux
MLX_INCLUDE = -Imlx_linux
CC			= @cc -g
# CFLAGS		= -Wall -Wextra -Werror -g3# -fsanitize=address,undefined
MLX_FLAGS 	= -L$(MLX_DIR) -lmlx -lmlx_Linux -L/usr/lib -lXext -lX11 -lm

all:		$(NAME)

$(NAME):	$(SRC)
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR)
			@$(MAKE) --no-print-directory -C $(MLX_DIR)
			$(CC) $(CFLAGS) $(^) $(MLX_FLAGS) -o $(@) $(LIBFT)

clean:
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) clean
			@$(MAKE) --no-print-directory -C $(MLX_DIR) clean

fclean:		clean
			@$(MAKE) --no-print-directory -C $(LIBFT_DIR) fclean
			@$(MAKE) --no-print-directory -C $(MLX_DIR) clean
			@rm -f $(NAME)

mem: all
			valgrind --log-file="val.log" --track-fds=yes --show-leak-kinds=all --leak-check=full ./cub3D maps/map1.cub
run:  all
			./$(NAME) maps/map1.cub

lib:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) re

re:			fclean all

.PHONY:		all clean fclean re