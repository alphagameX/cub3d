#include "../cub3d.h"


void	header_bmp(t_game *game, t_bmp *bmp)
{
	bmp->file_size = bmp->pixel_data_offset + (game->size.width *
			game->size.height * 4);
	write(bmp->fd, "BM", 2);
	write(bmp->fd, &bmp->file_size, 4);
	write(bmp->fd, "\0\0\0\0", 4);
	write(bmp->fd, &bmp->pixel_data_offset, 4);
}

void	info_img_bmp(t_game *game, t_bmp *bmp)
{
	bmp->img_size = game->size.width * game->size.height;
	write(bmp->fd, &bmp->header_size, 4);
	write(bmp->fd, &game->size.width, 4);
	write(bmp->fd, &game->size.height, 4);
	write(bmp->fd, &bmp->plane, 2);
	write(bmp->fd, &game->render.frame.bits_per_pixel, 2);
	write(bmp->fd, "\0\0\0\0", 4);
	write(bmp->fd, &bmp->img_size, 4);
	write(bmp->fd, "\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0\0", 16);
}

void	fill_bmp(t_game *game, t_bmp *bmp)
{
	int tab[3];
	int x;
	int y;

	y = game->size.height - 1;
	while (y >= 0)
	{
		x = 0;
		while (x < game->size.width)
		{
			tab[0] = game->render.frame.addr[y * game->render.frame.line_length +
				x * game->render.frame.bits_per_pixel / 8];
			tab[1] = game->render.frame.addr[y * game->render.frame.line_length +
				x * game->render.frame.bits_per_pixel / 8 + 1];
			tab[2] = game->render.frame.addr[y * game->render.frame.line_length +
				x * game->render.frame.bits_per_pixel / 8 + 2];
			write(bmp->fd, &tab[0], 1);
			write(bmp->fd, &tab[1], 1);
			write(bmp->fd, &tab[2], 1);
			write(bmp->fd, "\0", 1);
			x++;
		}
		y--;
	}
}

void	file_bmp(t_game *game)
{
	game->bmp.pixel_data_offset = 54;
	game->bmp.header_size = 40;
	game->bmp.plane = 1;
	if ((game->bmp.fd = open("save.bmp", O_CREAT | O_RDWR, S_IRWXU)) == -1) {
		ft_putstr("Error\n");
		ft_putstr("Cannot create bmp file\n");
		destroy_game(game);
	}
	header_bmp(game, &game->bmp);
	info_img_bmp(game, &game->bmp);
	fill_bmp(game, &game->bmp);
	close(game->bmp.fd);
	ft_putstr("Bmp file successfuly created !\n");
	destroy_game(game);
}
