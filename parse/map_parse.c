#include "cub3d.h"

bool	wall_check(char **map)
{
	int i = 0;
	int j = 0;
	while(map[0][i])
	{
		if(map[0][i] != '1' && map[0][i] != '\n')
		{
			printf("Walls is not correct\n");
			return(false);
		}
		i++;
	}
	i = 0;
	while(map[i])
		i++;
	i -= 1;
	while(map[i][j])
	{
		if(map[i][j] != '1' && map[i][j] != '\n')
		{
			printf("Walls is not correct\n");
			return(false);
		}
		j++;
	}
	return(true);
}

bool	player_chk(t_map_chk *info)
{
	int c = 0;
	int i = 0;
	int j = 0;

	char **map = info->map;
	while(map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if(map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'S'
				|| map[i][j] == 'W')
			{
				info->p_x = j;
				info->p_y = i;
				c++;
			}
			j++;
		}
		i++;
	}
	if(c == 0)
	{
		printf("No player start position\n");
		return(false);
	}
	else if(c > 1)
	{
		printf("Multiple player start positions");
		return(false);
	}
	else
		return(true);
}

void	put_marks(char **map, int x, int y)
{
	map[y][x] = '*';
	if(map[y - 1][x] != '1' && map[y - 1][x] != '*')
		put_marks(map, x, y - 1);
	if(map[y + 1][x] != '1' && map[y + 1][x] != '*')
		put_marks(map, x, y + 1);
	if(map[y][x - 1] != '1' && map[y][x - 1] != '*')
		put_marks(map, x - 1, y);
	if(map[y][x + 1] != '1' && map[y][x + 1] != '*')
		put_marks(map, x + 1, y);
}

bool	move_chk(t_map_chk *info)
{
	char **cpy_map;
	int i = 0;
	int j = 0;

	cpy_map = map_copy(info->map);
	put_marks(cpy_map, info->p_x, info->p_y);
	while(cpy_map[i])
	{
		j = 0;
		while(cpy_map[i][j])
		{
			if(cpy_map[i][j] != '1' && cpy_map[i][j] != '\n' && cpy_map[i][j] != '*')
			{
				printf("No movement area for player\n");
				return(false);
			}
			j++;
		}
		i++;
	}
	return(true);
}

bool    map_parse(t_map_chk *info)
{
	int i = 0;
	int j = 0;

	while(info->map[i])
	{
		j = 0;
		while (info->map[i][j])
		{
			if(!is_valid_char(info->map[i][j]))
			{
				printf("İnavlid char in map\n");
				return(false);
			}
			j++;
		}
		i++;
	}
	i = 1;
	while(info->map[i])
	{
		j = ft_strlen(info->map[i]) - 2;
		if(info->map[i][0] != '1' || info->map[i][j] != '1')
		{
			printf("Walls is not correct\n");
			return(false);
		}
		i++;
	}
	if(!wall_check(info->map) || !player_chk(info) || !move_chk(info))
		return(false);
	return(true);
}