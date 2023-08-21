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


SRC = $(wildcard ./src/*.c)
OBJS_DIR = objs
OBJS = $(addprefix $(OBJS_DIR)/, $(notdir $(SRC:.c=.o)))
DEPS =$(addprefix $(OBJS_DIR)/, $(notdir $(SRC:.c=.d)))

MLX_PATH = ./minilibx_opengl
MLX_NAME = libmlx.a
MLX = $(MLX_PATH)/$(MLX_NAME)

NAME = minitest

all: $(MLX) $(NAME)

$(MLX):
	@echo "Building the MiniLibX"
	@make -sC $(MLX_PATH) all
	@cp $(MLX) .  

-include $(DEPS)
$(NAME): $(OBJS)
	$(CC)  -o $(NAME) $(OBJS) $(GRAPH_LINKING)

$(OBJS_DIR):
	mkdir $(OBJS_DIR)

$(OBJS_DIR)/%.o: src/%.c | $(OBJS_DIR) 
	$(CC) $(FLAGS) $(GRAPH_COMPILE) -c $< -o $@

clean:
	make -C $(MLX_PATH) clean
	rm -rf $(OBJS_DIR)

fclean: clean
	rm -rf $(NAME) $(MLX_NAME)

re: fclean all

.PHONY: all re clean fclean
