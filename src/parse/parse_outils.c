#include "../../inc/cube3d.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\v'
		|| c == '\f');
}

size_t	count_clean_line(char *s)
{
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	while (s[i] && (ft_isspace(s[i])))
		i++;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
			len++;
		i++;
	}
	return (len);
}

void	count_w_h(t_map *map)
{
	int		i;
	size_t	biggest_line;

	map->map_height = count_double_char(map->map);
	i = 0;
	biggest_line = 0;
	while (map->map[i])
	{
		if (count_clean_line(map->map[i]) > biggest_line)
			biggest_line = count_clean_line(map->map[i]);
		i++;
	}
	map->map_width = biggest_line;
}

void	get_x_y(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			{
				map->x = i;
				map->y = j;
				return ;
			}
			j++;
		}
		i++;
	}
}
void	check_direction(t_map *map)
{
	get_x_y(map);
	if (map->map[map->x][map->y] == 'N')
		map->start_angle = 0;
	if (map->map[map->x][map->y] == 'S')
		map->start_angle = PI;
	if (map->map[map->x][map->y] == 'E')
		map->start_angle = 3*PI / 2;
	if (map->map[map->x][map->y] == 'W')
		map->start_angle = PI / 2;
}