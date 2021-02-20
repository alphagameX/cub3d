#include "../parsing.h"

void free_texture(t_game *game) {
    if(game->texture.ea.path)
        free(game->texture.ea.path);
    if(game->texture.we.path)
        free(game->texture.we.path);
    if(game->texture.so.path)
        free(game->texture.so.path);
    if(game->texture.no.path)
        free(game->texture.no.path);
     if(game->box.sprite.path)
        free(game->box.sprite.path);
}

void free_image(t_game *game) {
    if(game->texture.ea.tex.img != NULL)
        mlx_destroy_image(game->render.mlx, game->texture.ea.tex.img);
    if(game->texture.no.tex.img != NULL)
        mlx_destroy_image(game->render.mlx, game->texture.no.tex.img);
    if(game->texture.we.tex.img != NULL)
        mlx_destroy_image(game->render.mlx, game->texture.we.tex.img);
    if(game->texture.so.tex.img != NULL)
        mlx_destroy_image(game->render.mlx, game->texture.so.tex.img);
    if(game->box.sprite.frame.img != NULL)
        mlx_destroy_image(game->render.mlx, game->box.sprite.frame.img);
    if(game->render.frame.img != NULL)
        mlx_destroy_image(game->render.mlx, game->render.frame.img);
}

void destroy_game(t_game *game) {
    free_texture(game);
    if(game->render.ray.zbuf)
        free(game->render.ray.zbuf);
    if(game->box.sprite.nb_sprite > 0)
        free(game->box.sprite.data);
    if(game->map.height != 0 && game->map.width != 0)
        free_array(game->map.tmap);
    free_image(game);
    if(game->render.win != NULL) {
        mlx_destroy_window(game->render.mlx, game->render.win);
        mlx_destroy_display(game->render.mlx);
        free(game->render.mlx);
    }
    exit(0);
}

