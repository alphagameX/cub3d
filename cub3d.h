/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/21 20:31:44 by user42            #+#    #+#             */
/*   Updated: 2021/02/21 21:06:11 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_CUB3D_H
# define CUB3D_CUB3D_H
# include <fcntl.h>
# include "math.h"
# include "stdio.h"
# include "super-libft/libft.h"
# if OS == 0
#  include "mlx_linux/mlx.h"
# else
#  include "mlx/mlx.h"
# endif

typedef struct	s_settings
{
	double		move_speed;
	double		hit_distance;
	double		rot_speed;
	int			bmp_required;
}				t_settings;

typedef struct	s_rgb
{
	int			color;
	int			is_see;
}				t_rgb;

typedef struct	s_size
{
	int			width;
	int			height;
	int			is_see;
}				t_size;

typedef struct	s_lines
{
	char		**all;
	int			nb_line;
}				t_lines;

typedef struct	s_spawn
{
	char		dir;
	double		x;
	double		y;
}				t_spawn;

typedef struct	s_tmap
{
	int			width;
	int			height;
	t_spawn		spawn;
	t_lines		gnl;
	char		*smap;
	char		**tmap;
}				t_tmap;

typedef struct	s_frame
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			width;
	int			height;
}				t_frame;

typedef struct	s_scoord
{
	double		x;
	double		y;
}				t_scoord;

typedef struct	s_sprite
{
	char		*path;
	t_frame		frame;
	t_scoord	*data;

	double		inv_det;
	int			sprite_screen_x;
	int			sprite_height;
	int			sprite_width;
	int			draw_start_y;
	int			draw_start_x;
	int			draw_end_y;
	int			draw_end_x;
	int			nb_sprite;
	int			is_see;
}				t_sprite;

typedef struct	s_box
{
	t_rgb		floor;
	t_rgb		sky;
	t_sprite	sprite;
}				t_box;

typedef struct	s_wall
{
	double		wall_x;
	int			tex_x;
	int			tex_y;
	double		tex_pos;
	int			y;
}				t_wall;

typedef struct	s_tex
{
	t_frame		tex;
	int			is_see;
	char		*path;
}				t_tex;

typedef struct	s_texture
{
	t_tex		no;
	t_tex		so;
	t_tex		we;
	t_tex		ea;
}				t_texture;

typedef struct	s_ray
{
	double		*zbuf;
	double		angle_x;
	int			step_x;
	int			step_y;
	double		ray_dir_y;
	double		ray_dir_x;
	double		side_dist_x;
	double		side_dist_y;
	double		delta_dist_y;
	double		delta_dist_x;
	double		perp_wall_dist;
	int			map_x;
	int			map_y;
	int			line_height;
	int			draw_start;
	int			draw_end;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_ray;

typedef struct	s_move
{
	int			wait_mode[10];
	int			nb_move;
}				t_move;

typedef struct	s_render
{
	void		*mlx;
	void		*win;
	t_ray		ray;
	t_frame		frame;
	t_move		moves;
}				t_render;

typedef struct	s_bmp
{
	int			pixel_data_offset;
	int			header_size;
	int			plane;
	int			file_size;
	int			fd;
	int			img_size;
}				t_bmp;

typedef struct	s_game
{
	t_size		size;
	t_texture	texture;
	t_box		box;
	t_tmap		map;
	t_render	render;
	t_settings	settings;
	t_bmp		bmp;
}				t_game;

t_game			parsing(char *file);
char			*is_valid_path(char *path);
void			arguement_detection(int argv, char **argc, t_game *game);
double			get_param(t_game *game, char *param);
void			debug_map(t_game game);
void			destroy_game(t_game *game);
void			start(t_game *game);
void			generate_textures(t_game *game);
void			register_hook(t_game *game);
int				leave_game(t_game *game);
void			set_dir(t_game *game);
int				set_move(int key_code, t_move *moves);
int				unset_move(int key_code, t_move *moves);
int				rendering(t_game *game);
int				move(t_game *game);
void			turn_left(t_game *game, double rot_speed);
void			turn_right(t_game *game, double rot_speed);
void			set_start_ray(int x, t_game *game);
void			ray_dir(t_game *game, int map_x, int map_y);
void			dda(t_game *game, int *side);
void			line_height(t_game *game);
void			wall_casting(t_game *game, int side, int x);
void			my_mlx_pixel_put(t_frame *data, int x, int y, int color);
char			*get_color(char **addr, int width, int y, int x);
void			sprite_casting(t_game *game);
void			draw_one_sprite(t_game *game, int stripe, int tex_y, int tex_x);
void			sort_sprite(t_sprite *sprite, t_spawn spawn);
void			file_bmp(t_game *game);

#endif
