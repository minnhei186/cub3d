# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 13:49:56 by dhosokaw          #+#    #+#              #
#    Updated: 2025/02/11 16:44:59 by nkannan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror
INCDIR=-Iinclude

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	FRAMEWORKS = -lXext -lX11 -lm
else
	FRAMEWORKS = -framework OpenGL -framework AppKit
endif

LIBFTDIR=libft

ifeq ($(UNAME_S),Linux)
	LIBMINIDIR=minilibx-linux
else
	LIBMINIDIR=minilibx
endif

SRCS = \
src/copy.c \
src/draw.c \
src/draw_info.c \
src/error.c \
src/free.c \
src/game_init.c \
src/get_color.c \
src/load_data.c \
src/load_data_utils.c \
src/load_data_utils2.c \
src/load_texture.c \
src/main.c \
src/map_init.c \
src/move.c \
src/parse_map.c \
src/parse_map_utils.c \
src/parse_map_utils_error.c \
src/parser_line.c \
src/process_line_error.c \
src/process_lines_error.c \
src/ray_casting.c \
src/rotate.c \
src/set_direction.c \
src/texture.c \
src/use_data.c \
src/utils.c \
src/validate_close_data.c \
src/validation.c \
src/event.c

OBJS=$(SRCS:.c=.o)

LIB_ft=libft.a
LIB_mini=libmlx.a
NAME=cub3D

all:$(LIB_ft) $(LIB_mini) $(NAME)

$(NAME):$(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFTDIR)/$(LIB_ft)  $(LIBMINIDIR)/$(LIB_mini) $(FRAMEWORKS)

%.o: %.c
	$(CC) $(CFLAGS) $(INCDIR) -g -c $< -o $@

$(LIB_ft):
	$(MAKE) -C $(LIBFTDIR)
$(LIB_mini):
	$(MAKE) -C $(LIBMINIDIR)


clean:
	$(MAKE) clean -C $(LIBFTDIR)
	$(MAKE) clean -C $(LIBMINIDIR)
	rm -rf $(OBJS)
fclean:clean
	$(MAKE) fclean -C $(LIBFTDIR)
	rm -f $(NAME)

re:fclean all

.PHONY:all clean fclean re
