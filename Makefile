# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/21 13:58:06 by rjobert           #+#    #+#              #
#    Updated: 2023/08/21 13:58:10 by rjobert          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

FLAGS = -Wall -Wextra -Werror -I/. -MMD
GRAPH_COMPILE = -Imlx
GRAPH_LINKING = -L. -lmlx -framework OpenGL -framework Appkit


SRC = colors.c events.c init.c julia_set.c main.c mandelbrot_set.c rendering.c
OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRC:.c=.o)))
DEPS =$(addprefix $(OBJS_DIR)/, $(notdir $(SRC:.c=.d)))

MLX_PATH = ./minilibx_opengl
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)/$(MLX_NAME)

LIBFT_PATH = ./libft
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)/$(LIBFT_NAME)

NAME = fractol

all: $(MLX) $(LIBFT) $(NAME)

$(MLX):
	@echo "Building the MiniLibX"
	@make -sC $(MLX_PATH) all
	@cp $(MLX) .  

$(LIBFT):
	make -sC $(LIBFT_PATH) all

-include $(DEPS)
$(NAME): $(OBJS)
	$(CC) -o $(NAME) $(LIBFT) $(OBJS)  $(GRAPH_LINKING)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(OBJS_DIR)/%.o: src/%.c | $(OBJS_DIR) 
	$(CC) $(FLAGS) $(GRAPH_COMPILE) -c $< -o $@

clean:
	make -C $(MLX_PATH) clean
	make -C $(LIBFT_PATH) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	make -C $(LIBFT_PATH) fclean
	rm -rf $(NAME) $(MLX_NAME)

re: fclean all

.PHONY: all re clean fclean
