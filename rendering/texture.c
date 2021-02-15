#include "../cub3d.h"

void new_texture(void *mlx, char *path, t_frame *tex) {
    tex->img = mlx_xpm_file_to_image(mlx, path, &tex->width, &tex->height);
    tex->addr = mlx_get_data_addr(tex->img, &tex->bits_per_pixel, &tex->line_length, &tex->endian);
}

void generate_textures(t_game *game) {
    new_texture(game->render.mlx, game->texture.no.path, &game->texture.no.tex);
    new_texture(game->render.mlx, game->texture.so.path, &game->texture.so.tex);
    new_texture(game->render.mlx, game->texture.we.path, &game->texture.we.tex);
    new_texture(game->render.mlx, game->texture.ea.path, &game->texture.ea.tex);
}