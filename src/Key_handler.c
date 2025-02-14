
#include "cub3D.h"

int press_key(int keycode, t_game *game)
{
	if (keycode == XK_Escape)
		close_window(game);
	if (keycode == XK_a)
		game->player.move_x = -1;
	if (keycode == XK_d)
		game->player.move_x = 1;
	if (keycode == XK_w)
		game->player.move_y = 1;
	if (keycode == XK_s)
		game->player.move_y = -1;
}
