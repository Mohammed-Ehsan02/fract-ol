# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkhan <mkhan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/13 17:06:53 by amalbrei          #+#    #+#              #
#    Updated: 2022/07/27 18:38:58 by mkhan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	fractol
CC		=	gcc
SUBDIR	=	libft
SUBLIB	=	ft
CFLAGS	=	-Wall -Wextra -Werror
RM		=	rm	-rf

SRCS 	=	test.c

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -Imlx -c $< -o $@

$(NAME): $(SRCS)
	$(MAKE) all -C mlx
	$(CC) $(CFLAGS) $(SRCS) -Lmlx -lmlx -framework OpenGL -framework AppKit -o $(NAME)

clean:
	$(MAKE) clean -C mlx

fclean: clean
	$(RM) $(NAME)
	$(MAKE) clean -C mlx

re: fclean $(NAME)

.PHONY = all clean fclean re
