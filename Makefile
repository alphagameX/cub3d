NAME = cub3d
PARSE = parsing/map.c \
        parsing/crash.c \
        parsing/init.c \
        parsing/getter.c \
        parsing/map_close.c

RENDER = rendering/render.c

OBJ = main.c $(PARSE) $(RENDER)

LIB = ./super-libft/

all:
	@gcc $(OBJ) -L $(LIB) -l ft -o $(NAME) -fsanitize=address -Wall -Wextra -Werror -Lmlx -lmlx -framework OpenGL -framework AppKit
	@./$(NAME) map.cub --debug

leak:
	valgrind ./$(NAME) --leak-check=full -v

