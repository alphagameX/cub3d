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
		 rendering/texture.c \
		 rendering/moves.c \
		 rendering/turns.c

OBJ = main.c $(PARSE) $(RENDER)
UNAME=$(shell uname)

LIB = ./super-libft/
FLAG = -Werror

UP = 122
DOWN = 115
LEFT = 100
RIGHT = 113
TURN_RIGHT = 65363
TURN_LEFT = 65361


ifeq ($(UNAME), Linux)
TARGET = -L./mlx -l mlx -L/usr/lib -lXext -lX11 -I/usr/include -lm -lz  -O3
UP = 122
DOWN = 115
LEFT = 100
RIGHT = 113
TURN_RIGHT = 65361
TURN_LEFT = 65363
ECHAP = 65307
endif

ifeq ($(UNAME), Darwin)
TARGET = -Lmlx -lmlx -framework OpenGL -framework AppKit
UP = 122
DOWN = 115
LEFT = 100
RIGHT = 113
TURN_RIGHT = 65361
TURN_LEFT = 65363
ECHAP = 65307
endif

all:
	@gcc $(OBJ) -L $(LIB) -l ft -o $(NAME) $(FLAG) $(TARGET)
	@./cub3d map.cub

re: all

linux:
	@gcc $(OBJ) -L $(LIB) -l ft -o $(NAME) $(FLAG) 


leak:
	valgrind ./$(NAME) --leak-check=full -v

