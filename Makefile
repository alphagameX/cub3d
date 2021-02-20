NAME = cub3d
CUB = map.cub
LIB = ./super-libft/
FLAG = -Werror -Wall -Wextra

#PARSING
TEXTURE = texture.c resolution.c box.c
MAP = $(addprefix map/, function.c propagation.c spawn.c tmap.c)
SPRITE = $(addprefix sprite/, add.c sort.c)
MODEL = $(TEXTURE) $(MAP) $(SPRITE)

MODELS = $(addprefix parsing/model/, $(MODEL))
SETUP = $(addprefix parsing/setup/, init.c param.c)
PARSE = parsing/parse.c $(SETUP) $(MODELS)

#RENDER
MOVE = $(addprefix rendering/moving/, moves.c turns.c)
RAYCASTING = $(addprefix rendering/raycasting/, loop.c ray.c sprite.c wall.c)
CORE = $(addprefix rendering/core/, input.c function.c)
RENDER = $(CORE) $(RAYCASTING) $(MOVE)

OBJ = main.c $(PARSE) $(RENDER)
UNAME=$(shell uname)

#CONTROL
UP = 122
DOWN = 115
LEFT = 100
RIGHT = 113
TURN_RIGHT = 65363
TURN_LEFT = 65361

#OS CHECK
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

#CONTROL DEFINE
KEY= -D UP=$(UP) -D DOWN=$(DOWN) -D RIGHT=$(RIGHT) -D LEFT=$(LEFT) -D TURN_RIGHT=$(TURN_RIGHT) -D TURN_LEFT=$(TURN_LEFT) -D ECHAP=$(ECHAP)


all:
	@gcc $(OBJ) -L $(LIB) -l ft -o $(NAME) $(FLAG) $(TARGET) $(KEY)
	@echo "Compilation done!"

re: fclean
	@echo "Recompliling libft"
	@cd $(LIB) && make all
	@echo "Recompliling cub3d"
	@make all

run:
	@./$(NAME) $(CUB) --debug speed=1 rot=1 hit=3
	
clean: 
	@rm -rf $(NAME)
	@echo "Cleanig cub3d"

fclean: clean
	@cd $(LIB) && make fclean
	
