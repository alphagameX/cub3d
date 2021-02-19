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

typedef struct s_settings {
    double speed;
    double colisions;
} t_settings;

typedef struct s_rgb {
    int color;
    int is_see;
} t_rgb;

typedef struct s_size {
    int width;
    int height;

    int is_see;
} t_size;



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

typedef struct s_scoord {
    double x;
    double y;
} t_scoord; 

typedef struct s_sprite {
    char *path;
    t_frame frame;
    t_scoord *data;

    int nb_sprite;
    int is_see;
} t_sprite;

typedef struct s_box {
    t_rgb floor;
    t_rgb sky;
    t_sprite c_sprite;
} t_box;

typedef struct s_tex {
    t_frame tex;
    int is_see;
    char *path;
} t_tex;

typedef struct s_texture {
    t_tex no;
    t_tex so;
    t_tex we;
    t_tex ea;
} t_texture;

typedef struct s_ray {


    double *zbuf;
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
char *is_valid_path(char *path);

t_game new_game();
void set_dir(t_game *game);

// parsing

t_game parsing(char *file);
void destroy_game(t_game *game);

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
int leave_game(t_game *game); 

// move
void forward(t_game *game, double colision);
void backward(t_game *game,  double colision);
void strate_left(t_game *game, double colision);
void strate_right(t_game *game, double colision);
void turn_left(t_game *game, double rot_speed);
void turn_right(t_game *game, double rot_speed);

#endif //CUB3D_CUB3D_H
