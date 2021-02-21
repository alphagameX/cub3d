NAME = cub3d
CUB = map.cub
LIB = ./super-libft/
FLAG = 

#PARSING
TEXTURE = texture.c box.c 
MAP = $(addprefix map/, function.c propagation.c spawn.c tmap.c)
SPRITE = $(addprefix sprite/, add.c sort.c)
MODEL = $(TEXTURE) $(MAP) $(SPRITE) resolution.c

MODELS = $(addprefix parsing/model/, $(MODEL))
SETUP = $(addprefix parsing/setup/, init.c param.c)
PARSE = parsing/parse.c $(SETUP) $(MODELS) 

#RENDER
MOVE = $(addprefix rendering/moving/, moves.c turns.c)
RAYCASTING = $(addprefix rendering/raycasting/, loop.c ray.c sprite.c sprite2.c wall.c)
CORE = $(addprefix rendering/core/, input.c function.c hook.c set_dir.c)
RENDER = $(CORE) $(RAYCASTING) $(MOVE) rendering/bmp.c

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
MLX_CLEAN = cd mlx_linux && make clean
MLX_ALL = cd mlx_linux && make all
MLX_RE = cd mlx_linux && make re

TARGET = -L./mlx_linux -l mlx -L/usr/lib -lXext -lX11 -I/usr/include -lm -lz  -O3 
UP = 122
DOWN = 115
LEFT = 100
RIGHT = 113
TURN_RIGHT = 65361
TURN_LEFT = 65363
ECHAP = 65307
OS = 0
OBJ += parsing/setup/destroy_linux.c rendering/core/start_linux.c
endif

ifeq ($(UNAME), Darwin)
MLX_CLEAN = cd mlx && make clean
MLX_ALL = cd mlx && make all
MLX_RE = cd mlx && make re

TARGET = -Lmlx -lmlx -framework OpenGL -framework AppKit 
UP = 13
DOWN = 1
LEFT = 2
RIGHT = 0
TURN_RIGHT = 123
TURN_LEFT = 124
ECHAP = 53
OS = 1
OBJ += parsing/setup/destroy_osx.c rendering/core/start_osx.c
endif

#CONTROL DEFINE
KEY= -D UP=$(UP) -D DOWN=$(DOWN) -D RIGHT=$(RIGHT) -D LEFT=$(LEFT) -D TURN_RIGHT=$(TURN_RIGHT) -D TURN_LEFT=$(TURN_LEFT) -D ECHAP=$(ECHAP)


all:
	@cd $(LIB) && make all
	@make mlx_all
	@gcc $(OBJ) -D OS=$(OS) -L $(LIB) -l ft -o $(NAME) $(FLAG) $(TARGET) $(KEY) 
	@echo "Compilation done!"

re: fclean
	@echo "Recompliling mlx"
	@$(MLX_RE)
	@echo "Recompliling libft"
	@cd $(LIB) && make all
	@echo "Recompliling cub3d"
	@make all

run:
	@./$(NAME) $(CUB)
save:
	@./$(NAME) $(CUB) --save
	
clean: 
	@rm -rf $(NAME)
	@echo "Cleanig cub3d"

fclean: clean
	@make mlx_clean
	@cd $(LIB) && make fclean

bonus: all

mlx_all:
	@$(MLX_ALL)

mlx_re:
	@$(MLX_RE)

mlx_clean:
	@$(MLX_CLEAN)