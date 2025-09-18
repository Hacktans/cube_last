#include "cub3d.h"

void game_engine(t_game *game, t_map_chk *info)
{
    game->init = mlx_init();
    if(!game->init)
        printf("Error\nmlx_init_error\n");
    mlx_get_screen_size(game->init, &info->max_x, &info->max_y);
    game->win = mlx_new_window((game->init), info->max_x, info->max_y, "cube3d");
    mlx_loop(game->init);
}