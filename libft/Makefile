# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: oharoon <oharoon@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/29 14:58:19 by oharoon           #+#    #+#              #
#    Updated: 2022/11/21 13:56:43 by oharoon          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= /bin/rm -f

NAME = libft.a

SRCS = ft_isascii.c ft_isprint.c ft_isalpha.c ft_isdigit.c ft_isalnum.c \
			ft_tolower.c ft_toupper.c ft_strlen.c ft_strlcpy.c ft_strlcat.c \
			ft_strchr.c ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c \
			ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c \
			ft_memchr.c ft_memcmp.c ft_strdup.c ft_calloc.c ft_itoa.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c ft_strmapi.c \
			ft_striteri.c \
			ft_putstr.c

OBJS	= $(SRCS:.c=.o)

BONUS			=	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
						ft_lstlast.c ft_lstadd_back.c \
						ft_lstdelone.c ft_lstclear.c \
						ft_lstiter.c ft_lstmap.c
BONUS_OBJS		= $(BONUS:.c=.o)

all: $(NAME)

run: $(NAME)

	$(CC) $(CFLAGS) $(NAME) -o main
	./main

$(NAME):	$(OBJS)
			ar -rcs $(NAME) $(OBJS)

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME)

re: clean
	rm -rf $(NAME)
	make all
	make clean

bonus:			$(OBJS) $(BONUS_OBJS)
				ar -rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	

.PHONY: all clean fclean re bonus