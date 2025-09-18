#ifndef CUB_3D_H
#define CUB_3D_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdlib.h>
#include "./gnl/get_next_line.h"
#include "./libft/libft.h"
#include "./minilibx-linux/mlx.h"

typedef struct s_map_chk
{
    char **full_file;
    char **map;
    char *NT;
    char *ST;
    char *WT;
    char *ET;
    char *F;
    char *C;
    int map_start;
    int p_x;
    int p_y;
    //bunlara bilgisayarın desteklediği
    //tam ekran boyutu yazıldı oyun tam ekran olarak açılacak
    int max_x;
    int max_y;
}   t_map_chk;

typedef struct s_player
{
    //haritadaki koordinat
    double x;
    double y;
    //bakılan yön vektörü
    double  dirx;
    double  diry;
    //


}   t_player;


typedef struct s_game
{
    void *mlx;
    void *win;
    void *init;
    t_player *player;
}   t_game ;


t_map_chk    *parse(char *file);
bool check_file_name(char *file);
bool	is_valid_file(char *file);
void game_engine(t_game *game, t_map_chk *info);
bool check_file_name(char *file);
bool	is_valid_file(char *file);
t_map_chk	*get_file(char *file, t_map_chk *info);
void 	get_map(t_map_chk *info);
bool	get_textures_and_map(t_map_chk *info);
void	free_dp(char **str);
bool	rgb_chk(char **colour);
bool	comma_chk(char *str);
bool    map_parse(t_map_chk *info);
bool	is_valid_char(char a);
char	**map_copy(char **map);

#endif