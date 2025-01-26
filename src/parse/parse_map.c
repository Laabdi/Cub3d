/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:42:06 by moaregra          #+#    #+#             */
/*   Updated: 2025/01/26 19:02:41 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int check_map_line(char *s)
{
    int i = 0;
    while (s[i] != '\0')
    {
        if (s[i] != '1' && s[i] != '0' && s[i] != 'N' && s[i] != 'S'
            && s[i] != 'E' && s[i] != 'W' && s[i] != '\t' && s[i] != ' ')
            return (1);
        i++;
    }
    return (0);
}
void	get_map_into2darray(t_map *map, char *av)
{
	int		lines;
	int		map_started;
	char	*s;
	char	**all_file;
	int		i;
	int		j;

	lines = 0;
	map_started = 0;
	s = get_file_in_char(av);
	all_file = split_file(s);
	i = 0;
	j = 0;
	while (all_file[i])
	{
		if (check_map_line(all_file[i]) == 0)
		{
			map_started = 1;
			lines++;
		}
		else if (map_started)
			break ;
		i++;
	}
	map->map = malloc(sizeof(char *) * (lines + 1));
	i = 0;
	map_started = 0;
	while (all_file[i])
	{
		if (check_map_line(all_file[i]) == 0)
		{
			map_started = 1;
			map->map[j] = ft_strdup(all_file[i]);
			j++;
		}
		else if (map_started)
			break ;
		i++;
	}
	map->map[j] = NULL;
	i = 0;
	while (all_file[i])
	{
		free(all_file[i]);
		i++;
	}
	free(all_file);
}
int	count_double_char(char **s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		i++;
	}
	return (i - 1);
}
int	check_borders(char *s)
{
	int	i;

	i = 0;
	int last_index = ft_strlen(s) - 1;
	while (s[i])
	{
		if (s[0] != '1' || s[last_index] != '1')
			return (1);
		i++;
	}
	return (0);
}
int	check_top_and_bottom(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != '1' || s[i] !=)
			return (1);
		i++;
	}
	return (0);
}
int check_map(t_map *map)
{
    int players = 0;
    int size = count_double_char(map->map);
    int i = 0;
    int j;

    // Check top and bottom rows are all walls
    if (check_top_and_bottom(map->map[0]) == 1 || 
        check_top_and_bottom(map->map[size]) == 1)
        return (0);

    // Comprehensive map validation
    while (map->map[i])
    {
        // Check borders of each line
        if (check_borders(map->map[i]) == 1)
            return (0);

        // Count player start positions and validate surrounding walls
        j = 0;
        while (map->map[i][j])
        {
            char c = map->map[i][j];
            
            // Count player start positions
            if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
            {
                players++;
                
                // Validate player is surrounded by walls
                if (i == 0 || i == size || j == 0 || 
                    map->map[i-1][j] == ' ' || map->map[i+1][j] == ' ' ||
                    map->map[i][j-1] == ' ' || map->map[i][j+1] == ' ')
                    return (0);
            }
            
            // Check open spaces are surrounded by walls
            if (c == '0')
            {
                if (i == 0 || i == size || j == 0 || 
                    map->map[i-1][j] == ' ' || map->map[i+1][j] == ' ' ||
                    map->map[i][j-1] == ' ' || map->map[i][j+1] == ' ')
                    return (0);
            }
            j++;
        }
        i++;
    }

    // Ensure exactly one player start position
    if (players != 1)
        return (0);

    return (1);
}