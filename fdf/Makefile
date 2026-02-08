# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddehili <ddehili@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/12/12 18:46:51 by ddehili           #+#    #+#              #
#    Updated: 2026/02/02 17:00:01 by ddehili          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = main.c get_next_line.c get_next_line_utils.c 3d_utils.c

OBJS = ${SRCS:.c=.o}

NAME = fdf_42

CC = cc

MLX_DIR = minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm

CFLAGS = -g3 -Wall -Werror -Wextra -I ./ -I$(MLX_DIR)
.c.o:
		${CC} ${CFLAGS} -c $< -o ${<:.c=.o}


${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} $(MLX_FLAGS) -o ${NAME}
	
all: 	${NAME}

run: ${NAME}
	./${NAME}

clean:	
		rm -f ${OBJS}

fclean:	clean;
		rm -f ${NAME}

re:	fclean all

.PHONY: all clean fclean re bonus
