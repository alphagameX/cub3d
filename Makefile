NAME = cub3d
PARSE = parsing/map.c \
        parsing/crash.c \
        parsing/init.c \
        parsing/getter.c \
        parsing/tmap.c

RENDER = rendering/render.c \
		 rendering/core.c \
		 rendering/texture.c

OBJ = main.c $(PARSE) $(RENDER)

LIB = ./super-libft/
FLAG = -Werror

all:
	@gcc $(OBJ) -L $(LIB) -l ft -o $(NAME) $(FLAG) -Lmlx -lmlx -framework OpenGL -framework AppKit
	@./$(NAME) map.cub --debug

leak:
	valgrind ./$(NAME) --leak-check=full -v

