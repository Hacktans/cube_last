#include "cub3d.h"

t_map_chk	*get_file(char *file, t_map_chk *info)
{
	char *line;
	int len = 0;
	int fd = open(file, O_RDONLY);
	while((line = get_next_line(fd)))
		len++;
	info->full_file = malloc(sizeof(char *) * (len + 1));
	len = 0;
	fd = open(file, O_RDONLY);
	while((line = get_next_line(fd)))
	{
		info->full_file[len] = line;
		len++;
	}
	info->full_file[len] = NULL;
	return(info);
}

void 	get_map(t_map_chk *info)
{
	int i = 0;
	int temp;
	int len = 0;
	while(info->full_file[i] && !(info->full_file[i][0] == '1' || info->full_file[i][0] == '0'))
		i++;
	temp = i;
	info->map_start = i + 1;
	while(info->full_file[temp])
	{
		len++;
		temp++;
	}
	info->map = malloc(sizeof(char *) * (len + 1));
	if(!info->map)
		return ;
	len = 0;
	while(info->full_file[i])
	{
		info->map[len] = info->full_file[i];
		i++;
		len++;
	}
	info->map[len] = NULL;
}

bool	get_textures_and_map(t_map_chk *info)
{
	int i = 0;
	int arg_c = 0;
	while(info->full_file[i])
	{
		if(ft_strncmp("NO ", info->full_file[i], 3) == 0)
		{
			info->NT = info->full_file[i];
			arg_c++;
		}
		if(ft_strncmp("SO ", info->full_file[i], 3) == 0)
		{
			info->ST = info->full_file[i];
			arg_c++;
		}
		if(ft_strncmp("EA ", info->full_file[i], 3) == 0)
		{
			info->ET = info->full_file[i];
			arg_c++;
		}
		if(ft_strncmp("WE ", info->full_file[i], 3) == 0)
		{
			info->WT = info->full_file[i];
			arg_c++;
		}
		if(ft_strncmp("F ", info->full_file[i], 2) == 0)
		{
			info->F = info->full_file[i];
			arg_c++;
		}
		if(ft_strncmp("C ", info->full_file[i], 2) == 0)
		{
			info->C = info->full_file[i];
			arg_c++;
		}
		i++;
	}
	if(arg_c != 6)
		return(false);
	get_map(info);
	return(true);
}
