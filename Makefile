# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 17:06:53 by amalbrei          #+#    #+#              #
#    Updated: 2022/08/10 18:03:58 by mkhan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol
CC		=	gcc
SUBDIR	=	libft
SUBLIB	=	ft
CFLAGS	=	-Wall -Wextra -g3 -Ofast
RM		=	rm	-rf

SRCS 	=	fractol.c events.c mandelbrot.c julia.c atof.c
OBJ		:= 	$(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	$(CC) -Wall -Wextra -I/usr/include -Imlx_linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) all -C mlx_linux
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME)
clean:
	$(MAKE) clean -C mlx_linux

fclean: clean
	$(RM) $(NAME) $(OBJ)

re: fclean $(NAME)

.PHONY = all clean fclean re
