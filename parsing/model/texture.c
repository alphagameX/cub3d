#include "../parsing.h"

int check_texture(t_texture texture) {
    if(!texture.ea.path || !texture.we.path || !texture.so.path || !texture.no.path)
        return (0);
    return (1);
}

void is_valid_texture(t_game *game) {
    if(check_texture(game->texture) == 0) {
        ft_putstr("Error\n");
        if(!game->texture.ea.path)
            ft_printf("This texture \"EA\" path is wrong or invalid xpm\n");
        if(!game->texture.no.path)
            ft_printf("This texture \"NO\" path is wrong or invalid xpm\n");
        if(!game->texture.so.path)
            ft_printf("This texture \"SO\" path is wrong or invalid xpm\n");
        if(!game->texture.we.path)
            ft_printf("This texture \"WE\" path is wrong or invalid xpm\n");
        destroy_game(game);
    }
}

void check_tex(t_tex *tex, t_game *game, char *type, char *param) {
     if(tex->is_see < 1) {
           tex->path = check_is_valid_texture_path(param);
           if(!tex->path)
                free(param);
           tex->is_see += 1; 
     } else {
        ft_putstr("Error\n");
        ft_printf("More than one %s arguments", type);
        free(type);
        free(param);
        destroy_game(game);
    }
}

void get_texture(char *line, t_game *game) {
    char **param = ft_split(line, ' ');
    int i = 0;

    while(param[i])
        i++;
    if(i != 2) {
        ft_putstr("Error\n");
        ft_printf("Wrong parameter in %s\n", param[0]);
        while(i > 0)
            free(param[i--]);
        free(param);
        destroy_game(game);
    }
    if(param[0][0] == 'N' && param[0][1] == 'O')
        check_tex(&game->texture.no, game, param[0], param[1]);
    if(param[0][0] == 'S' && param[0][1] == 'O')
        check_tex(&game->texture.so, game, param[0], param[1]);
    if(param[0][0] == 'W' && param[0][1] == 'E')
        check_tex(&game->texture.we, game, param[0], param[1]);
    if(param[0][0] == 'E' && param[0][1] == 'A')
        check_tex(&game->texture.ea, game, param[0], param[1]);
        
    free(param[0]);
    free(param);
}