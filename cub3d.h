//
// Created by Arthur Tinseau on 14/01/2021.
//

#ifndef CUB3D_CUB3D_H
#define CUB3D_CUB3D_H

#include <fcntl.h>
#include "mlx/mlx.h"
#include "math.h"
#include "stdio.h"
#include "super-libft/libft.h"


typedef struct s_size {
    int width;
    int height;
} t_size;


typedef struct s_box {
    char *c_floor;
    char *c_sky;
    char *c_sprite;
} t_box;

typedef struct s_spawn {
    char dir;
    double x;
    double y;
} t_spawn;

typedef struct s_tmap {
    int width;
    int height;
    t_spawn spawn;

    char **tmap;
} t_tmap;

typedef struct  t_frame {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
    int         width;
    int         height;
}               t_frame;

typedef struct s_tex {
    t_frame tex;
    char *path;
} t_tex;

typedef struct s_texture {
    t_tex no;
    t_tex so;
    t_tex we;
    t_tex ea;
} t_texture;

typedef struct s_ray {

    double angleX;
    int stepX, stepY;
    double rayDirX, rayDirY;
    double sideDistX, sideDistY;
    double deltaDistX, deltaDistY;
    double perpWallDist;

    int mapX, mapY;
    int lineHeight, drawStart, drawEnd;
    double dirX, dirY;
    double planeX, planeY;
} t_ray;

typedef struct s_move {
    int wait_mode[10];
    int nb_move;
} t_move;

typedef struct s_render {
    void *mlx;
    void *win;
    t_ray ray;
    t_frame frame;
    t_move moves;
} t_render;

typedef struct s_game {
    t_size size;
    t_texture texture;
    t_box box;
    t_tmap map;
    t_render render;
} t_game;


// init
t_game new_game();
void init_moves(t_move *moves);

// parsing

t_game parsing(char *file);
void destroy_map(t_game *game);

// getter
void get_resolution(char *res, t_size *size);
void get_texture(char *line, t_texture *texture);
int get_box(char *line, t_box *box);

// crasher
void exit_failure(char *msg);
void map_valid(t_game game);


// utils
void debug_map(t_game game);

// drawing

void my_mlx_pixel_put(t_frame *data, int x, int y, int color);
unsigned int my_mlx_pixel_get(t_frame *data, int x, int y);

// render
int rendering(t_game *game);
int move(t_game *game);

int set_move(int key_code, t_move *moves);
int unset_move(int key_code, t_move *moves);

//core
void my_mlx_pixel_put(t_frame *data, int x, int y, int color);
int new_image(t_game *game);
void generate_textures(t_game *game);

#endif //CUB3D_CUB3D_H
