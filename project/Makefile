# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dhosokaw <dhosokaw@student.42tokyo.>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/03 13:49:56 by dhosokaw          #+#    #+#              #
#    Updated: 2025/02/07 12:20:42 by hosokawa         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=cc 
CFLAGS=-Wall -Wextra -Werror
INCDIR=-Iinclude
FRAMEWORKS = -framework OpenGL -framework AppKit

LIBFTDIR=libft
LIBMINIDIR=minilibx

SRCS=$(wildcard src/*.c)
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
