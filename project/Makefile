# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nkannan <nkannan@student.42tokyo.jp>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 13:49:56 by dhosokaw          #+#    #+#              #
#    Updated: 2025/02/07 21:39:28 by nkannan          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc
CFLAGS=-Wall -Wextra -Werror

DEBUG_FLAGS=-g -fsanitize=address

# OSの判別とそれに応じた設定
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MLXDIR=minilibx-linux
	LIBS = -lmlx -lXext -lX11 -lm
else
	MLXDIR=minilibx
	LIBS = -lmlx -framework OpenGL -framework AppKit
endif

LIBFTDIR=libft
INCDIR=-Iinclude -I$(LIBFTDIR)/include -I$(MLXDIR)

SRCS=$(wildcard src/*.c)
OBJS=$(SRCS:.c=.o)

LIB_ft=libft/libft.a
LIB_mlx=$(MLXDIR)/libmlx.a
NAME=Wall


all: $(NAME)

debug: CFLAGS += $(DEBUG_FLAGS)
debug: $(NAME)


$(NAME): $(OBJS) $(LIB_ft) $(LIB_mlx)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIB_ft) $(LIB_mlx) $(LIBS) -L$(MLXDIR)

%.o: %.c
	$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

$(LIB_ft):
	$(MAKE) -C $(LIBFTDIR)

$(LIB_mlx):
ifeq ($(UNAME_S),Linux)
	$(MAKE) -C $(MLXDIR)
else # macOSの場合、minilibxのmakeは不要な場合が多い
	@echo "Skipping minilibx compilation on macOS (assuming precompiled library)"
#	$(MAKE) -C $(MLXDIR)  # 必要ならコメントアウトを外す
endif

clean:
	$(MAKE) clean -C $(LIBFTDIR)
ifeq ($(UNAME_S),Linux)
	$(MAKE) clean -C $(MLXDIR)  # Linuxの場合のみminilibxもclean
endif
	rm -f $(OBJS)

fclean: clean
	$(MAKE) fclean -C $(LIBFTDIR)
	rm -f $(NAME)

re: fclean all


.PHONY: all debug clean fclean re