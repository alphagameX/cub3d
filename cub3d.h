//
// Created by Arthur Tinseau on 14/01/2021.
//

#ifndef CUB3D_CUB3D_H
#define CUB3D_CUB3D_H

#include <fcntl.h>
#include "math.h"
#include "stdio.h"
#include "super-libft/libft.h"

#if OS == 0
#include "mlx_linux/mlx.h"
#endif

#if OS == 1
#include "mlx/mlx.h"
#endif 

typedef struct s_settings {
    double move_speed;
    double hit_distance;
    double rot_speed;
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

    double invDet;
    int spriteScreenX;
    int spriteHeight;
    int spriteWidth;

    int drawStartY;
    int drawStartX;
    int drawEndY;
    int drawEndX;

    int nb_sprite;
    int is_see;
} t_sprite;

typedef struct s_box {
    t_rgb floor;
    t_rgb sky;
    t_sprite sprite;
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
    t_settings settings;
} t_game;


// init
char *is_valid_path(char *path);
double get_param(t_game *game, char *param);

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
char *get_color(char **addr,int width,int y, int x);

// ray
void rayDir(t_game *game, int mapX, int mapY);
void set_start_ray(int x, t_game *game);
void dda(t_game *game, int *side);
void lineHeight(t_game *game);

// wall
void wall_casting(t_game *game, int side, int x);

// sprite
int relative_distance(t_spawn p, t_scoord s);
void swap_sprite(t_scoord *src, t_scoord *dst);
void sortSprite(t_sprite *sprite, t_spawn spawn);
void sprite_casting(t_game *game);

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
