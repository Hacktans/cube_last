#include "cub3d.h"

bool	file_structure(t_map_chk *info)
{
	int i = 0;
	while(i < info->map_start - 1)
	{
		if(ft_strncmp("NO ", info->full_file[i], 3) == 0 || ft_strncmp("WE ", info->full_file[i], 3) == 0
			|| ft_strncmp("EA ", info->full_file[i], 3) == 0 || ft_strncmp("SO ", info->full_file[i], 3) == 0
			|| ft_strncmp("F ", info->full_file[i], 2) == 0 || ft_strncmp("C ", info->full_file[i], 2) == 0
			|| info->full_file[i][0] == '\n')
			i++;
		else
			return(false);
	}
	return(true);
}

bool	same_direc(t_map_chk *info)
{
	int i = 0;
	int n_c = 0;
	int w_c = 0;
	int s_c = 0;
	int e_c = 0;
	while(i < info->map_start - 1)
	{
		if(ft_strncmp("NO ", info->full_file[i], 3) == 0)
			n_c++;
		if(ft_strncmp("SO ", info->full_file[i], 3) == 0)
			s_c++;
		if(ft_strncmp("WE ", info->full_file[i], 3) == 0)
			w_c++;
		if(ft_strncmp("EA ", info->full_file[i], 3) == 0)
			e_c++;
		i++;
	}
	if(n_c != 1 || w_c != 1 || e_c != 1 || s_c != 1)
		return(false);
	return(true);
}

bool	path_chk(t_map_chk *info)
{
	char *tmp;
	
	tmp = ft_strtrim(info->NT, "NO \n");
	if(!is_valid_file(tmp))
	{
		free(tmp);
		printf("Error : NO textures not found\n");
		return(false);
	}
	free(tmp);
	tmp = ft_strtrim(info->ST, "SO \n");
	if(!is_valid_file(tmp))
	{
		free(tmp);
		printf("Error : SO textures not found\n");
		return(false);
	}
	free(tmp);
	tmp = ft_strtrim(info->WT, "WE \n");
	if(!is_valid_file(tmp))
	{
		free(tmp);
		printf("Error : WE textures not found\n");
		return(false);
	}
	free(tmp);
	tmp = ft_strtrim(info->ET, "EA \n");
	if(!is_valid_file(tmp))
	{
		free(tmp);
		printf("Error : EA textures not found\n");
		return(false);
	}
	free(tmp);
	return(true);
}

bool	colour_format(t_map_chk *info)
{
	char *tmp;
	char **tmp2;

	tmp = ft_strtrim(info->F, "F \n");
	tmp2 = ft_split(tmp, ',');
	if(tmp2[3] || !rgb_chk(tmp2) || !comma_chk(tmp))
	{
		free(tmp);
		free_dp(tmp2);
		printf("Colour format must be RGB\n");
		return(false);
	}
	free(tmp);
	free_dp(tmp2);
	tmp = ft_strtrim(info->C, "C \n");
	tmp2 = ft_split(tmp, ',');
	if(tmp2[3] || !rgb_chk(tmp2) || !comma_chk(tmp))
	{
		free(tmp);
		free_dp(tmp2);
		printf("Colour format must be RGB\n");
		return(false);
	}
	free(tmp);
	free_dp(tmp2);
	return(true);
}

t_map_chk    *parse(char *file)
{
	int i = 0;
	t_map_chk *info;
	info = malloc(sizeof(t_map_chk));
	if(!check_file_name(file))
	{
		printf("File format must be \".cub\"\n");
		return NULL;
	}
	if(!is_valid_file(file))
	{
		printf("File not found\n");
		return NULL;
	}
	info = get_file(file, info);
	if(!get_textures_and_map(info) || !same_direc(info))
	{
		printf("Each element can only be defined once\n");
		return NULL;
	}
	if(!file_structure(info))
	{
		printf("Wrong file format\n");
		return NULL;
	}
	if(!path_chk(info) || !colour_format(info) || !map_parse(info))
		return NULL;
	printf("%s", info->NT);
	printf("%s", info->ET);
	printf("%s", info->ST);
	printf("%s", info->WT);
	printf("%s", info->F);
	printf("%s", info->C);
	while(info->map[i])
	{
		printf("%s", info->map[i]);
		i++;
	}
	return (info);
}