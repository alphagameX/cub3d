NAME = cub3d
PARSE = parsing/map.c \
        parsing/crash.c \
        parsing/getter.c \
        parsing/tmap.c \
		parsing/setup/init.c \
		parsing/model/texture.c \
		parsing/model/box.c \
		parsing/model/resolution.c \
		parsing/sprite/add.c

RENDER = rendering/render.c \
		 rendering/core.c \
		 rendering/texture.c

OBJ = main.c $(PARSE) $(RENDER)

LIB = ./super-libft/
FLAG = -Werror 

all:
	@gcc $(OBJ) -L $(LIB) -l ft -o $(NAME) $(FLAG) -Lmlx -lmlx -framework OpenGL -framework AppKit

re: all

leak:
	valgrind ./$(NAME) --leak-check=full -v

