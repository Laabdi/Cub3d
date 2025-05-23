/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 15:38:42 by moaregra          #+#    #+#             */
/*   Updated: 2025/05/16 16:55:01 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

void	parse_texture(t_map *map, char *line, char *identifier, char **dest)
{
	char	*tmp;

	(void)map;
	if (ft_strnstr(line, identifier, ft_strlen(line)))
	{
		tmp = ft_strdup(line);
		if (!tmp)
			return ;
		*dest = parse_line(tmp, identifier);
		free(tmp);
	}
}

void	fill_struct_helper(t_map *map, char **file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		parse_texture(map, file[i], "NO ", &map->no);
		parse_texture(map, file[i], "SO ", &map->se);
		parse_texture(map, file[i], "EA ", &map->ea);
		parse_texture(map, file[i], "WE ", &map->we);
		parse_texture(map, file[i], "F ", &map->floor_color);
		parse_texture(map, file[i], "C ", &map->celling_color);
		i++;
	}
}

void	fill_struct(t_map *map, char *av)
{
	char	*s;
	char	**file;
	int		i;

	s = get_file_in_char(av);
	if(s == NULL)
		return ;
	file = split_file(s);
	if (!s || !file || !map)
		return;
	i = 0;
	if(validate_textures(file) == 1)
	printf("valid arguments\n");
	else
	{
		while (file[i])
			{
				free(file[i]);
				i++;
			}
			free(file);
			free(s);
			printf("double arguments \n");
			exit(1);
	}
	fill_struct_helper(map, file);
	i = 0;
	while (file[i])
	{
		free(file[i]);
		i++;
	}
	free(file);
	free(s);
}

void	initiliase_struct(t_map *map, char *av)
{
	fill_struct(map, av);
	if(check_texture(map) == 0)
	{
		free_map_struct(map);
		printf("non valid texture\n");
		exit(1);
	}
	fill_rgb(map);
}
