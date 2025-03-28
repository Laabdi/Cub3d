CC = cc
FLAGS = -Wall -Wextra -Werror -fsanitize=address
SRCS = src/parse/main2.c src/parse/parse_outils.c src/parse/parse_helpers.c src/parse/parse_helpers2.c src/parse/parse_helpers3.c src/parse/parse_map.c src/parse/parse_mapv2.c src/parse/parse_mapv3.c  src/parse/parse.c
LIB = libft/libft.a
NAME = cub3D
OBJ = $(SRCS:.c=.o)

GREEN = \033[0;32m
YELLOW = \033[0;33m
RED = \033[0;31m
NC = \033[0m

all : $(NAME) $(LIB)

$(LIB):
	$(MAKE) -C libft/

$(NAME): $(OBJ) $(LIB)
	$(CC) $(OBJ) -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -lXext -lX11 -lm -lz -o $(NAME) $(LIB)

%.o: %.c
	$(CC) -Wall -Wextra -Werror -I/usr/include -Imlx_linux -O3 -c $< -o $@

clean :
	$(MAKE) clean -C libft/
	@rm -f $(OBJ)
	@echo "$(RED)Cleaning"
	@sleep 0.5
	@echo -n .
	@sleep 0.5
	@echo -n .
	@sleep 0.5
	@echo -n .
	@sleep 0.5
	@echo ".$(NC)"

fclean : clean
	$(MAKE) fclean -C libft/
	@rm -rf $(NAME)

re : fclean all 

.PHONY: all clean fclean re

.SECONDARY: $(OBJ)