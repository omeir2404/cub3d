NAME = 		cub3D
SRC =       parsing/arg_check.c parsing/test_main.c
LIBFT_DIR	= libft
LIBFT		= libft/libft.a
MLX_DIR		= ./mlx_linux
MLX_INCLUDE = -Imlx_linux
CC			= @cc
CFLAGS		= -Wall -Wextra -Werror -g3# -fsanitize=address,undefined
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

lib:
	@$(MAKE) --no-print-directory -C $(LIBFT_DIR) re

re:			fclean all

.PHONY:		all clean fclean re