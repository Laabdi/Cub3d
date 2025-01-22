/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_helpers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:38:53 by moaregra          #+#    #+#             */
/*   Updated: 2025/01/22 13:24:23 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

size_t	ft_strlenewline(char *s)
{
	size_t	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

static char	*get_file_in_char(char *av)
{
	char		*line;
	int			fd;
	static char	*map = NULL;
	char		*temp;

	fd = open(av, O_RDONLY);
	if (fd == -1)
	{
		printf("Error opening file\n");
		exit(1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		if (map == NULL)
			map = ft_strdup(line);
		else
		{
			temp = ft_strjoin(map, line);
			free(map);
			map = temp;
		}
		free(line);
	}
	close(fd);
	return (map);
}

char	**split_file(char *s)
{
	char	**all_line;
	char	**clean_line;
	int		i;
	int		j;
	int		count;

	if (!s)
		return (NULL);
	all_line = ft_split(s, '\n');
	if (!all_line)
		return (NULL);
	count = 0;
	i = 0;
	while (all_line[i])
	{
		if (all_line[i][0] != '\n')
			count++;
		i++;
	}
	clean_line = malloc(sizeof(char *) * (count + 1));
	if (!clean_line)
	{
		i = 0;
		while (all_line[i])
			free(all_line[i++]);
		free(all_line);
		return (NULL);
	}
	i = 0;
	j = 0;
	while (all_line[i])
	{
		if (all_line[i][0] != '\n')
		{
			clean_line[j] = ft_strdup(all_line[i]);
			if (!clean_line[j])
			{
				while (j > 0)
					free(clean_line[--j]);
				free(clean_line);
				return (NULL);
			}
			j++;
		}
		free(all_line[i]);
		i++;
	}
	clean_line[j] = NULL;
	free(all_line);
	return (clean_line);
}
char	*parse_line(char *s, char *to_trim)
{
	char	*new;
	char	*result;
	int		len;
	int		i;
	int		j;

	new = ft_strtrim(s, to_trim);
	i = 0;
	j = 0;
	if (!new)
		return (NULL);
	len = ft_strlen(new);
	result = malloc(sizeof(char) * (len + 1));
	if (!result)
	{
		free(new);
		return (NULL);
	}
	// Copy non-space characters
	while (new[i])
	{
		if (new[i] != ' ' && new[i])
		{
			result[j] = new[i];
			j++;
		}
		i++;
	}
	result[j] = '\0';
	free(new);
	return (result);
}
void	fill_struct(t_map *map,char *av)
{
	char	*s;
	char	**file;
	char	*tmp;
	int		i;

	s = get_file_in_char(av);
	file = split_file(s);
	i = 0;
	if (!s || !file || !map)
		return ;
	while(file[i])
	{
		if (ft_strnstr(file[i], "NO ", ft_strlen(file[i])))
		{
			tmp = ft_strdup(file[i]);
			if (!tmp)
				return ;
			map->no = parse_line(tmp, "NO ");
			free(tmp);
		}
		if (ft_strnstr(file[i], "SO ", ft_strlen(file[i])))
		{
			tmp = ft_strdup(file[i]);
			if (!tmp)
				return ;
			map->se = parse_line(tmp, "SO ");
			free(tmp);
		}
		if (ft_strnstr(file[i], "EA ", ft_strlen(file[i])))
		{
			tmp = ft_strdup(file[i]);
			if (!tmp)
				return ;
			map->ea = parse_line(tmp, "EA ");
			free(tmp);
		}
		if (ft_strnstr(file[i], "WE ", ft_strlen(file[i])))
		{
			tmp = ft_strdup(file[i]);
			if (!tmp)
				return ;
			map->we = parse_line(tmp, "WE ");
			free(tmp);
		}
		i++;
	}
}

// int	main(void)
// {
// 	t_map map;
// 	fill_struct(&map);
// 	printf("%s\n", map.no);
// 	printf("%s\n", map.se);
// 	printf("%s\n", map.ea);
// 	printf("%s\n", map.we);
// 	return (0);
// }