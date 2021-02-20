NAME = cub3d

PARSE_MODEL = $(addprefix parsing/model/, texture.c)

# PARSING
MAP = $(addprefix map/, function.c propagation.c spawn.c tmap.c)
SPRITE = $(addprefix sprite/, add.c sort.c)
MODEL = texture.c \
		resolution.c \
		box.c \
		$(MAP) \
		$(SPRITE)

MODELS = $(addprefix parsing/model/, $(MODEL))
SETUP = $(addprefix parsing/setup/, init.c param.c)


PARSE = parsing/parse.c \
		$(SETUP) \
		$(MODELS)

RENDER = rendering/moving/moves.c \
		 rendering/moving/turns.c \
		 rendering/raycasting/loop.c \
		 rendering/raycasting/ray.c \
		 rendering/raycasting/sprite.c \
		 rendering/raycasting/wall.c \
		 rendering/core/input.c \
		 rendering/core/function.c

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
UP = 13
DOWN = 1
LEFT = 2
RIGHT = 0
TURN_RIGHT = 123
TURN_LEFT = 124
ECHAP = 53
TARGET = -Lmlx -lmlx -framework OpenGL -framework AppKit
endif

KEY= -D UP=$(UP) -D DOWN=$(DOWN) -D RIGHT=$(RIGHT) -D LEFT=$(LEFT) -D TURN_RIGHT=$(TURN_RIGHT) -D TURN_LEFT=$(TURN_LEFT) -D ECHAP=$(ECHAP)

all:
	@gcc $(OBJ) -L $(LIB) -l ft -o $(NAME) $(FLAG) $(TARGET) $(KEY)
	@./cub3d map.cub speed=5 hit=30 rot=7 --debug

re: all

clean: 
	rm -rf $(NAME)

fclean: clean re

leak:
	valgrind ./$(NAME) --leak-check=full -v

