#include "cub3d.h"

void game_engine(t_game *game, t_map_chk *info)
{
    game->init = mlx_init();
    if(!game->init)
        printf("Error\nmlx_init_error\n");
    info->max_x = 1920;
    info->max_y = 1080;
    game->win = mlx_new_window((game->init), info->max_x, info->max_y, "cube3d");
    mlx_loop(game->init);
}