/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 13:42:06 by moaregra          #+#    #+#             */
/*   Updated: 2025/01/23 19:10:27 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int check_map_line(char *s)
{
    int i = 0;
    while(s[i])
    {
        if(s[i] != '1' && s[i] != '0' && s[i] != 'N' && s[i] != 'S' && s[i] != 'E' && s[i] != 'W')
        return 1;
        i++;
    }
    return 0;
}
void   get_map_into2darray(t_map *map,char *av)
{
    int lines = 0;
    char *s = get_file_in_char(av);
    char **all_file = split_file(s);
    int i = 0;
    int j = 0;
    while(all_file[i])
    {
        if(check_map_line(all_file[i]) == 0)
        {
            lines++;
        }
            i++;        
    }
    i = 0;
map->map = malloc(sizeof(char *) * (lines + 1));
    while(all_file[i])
    {
        if(check_map_line(all_file[i]) == 0)
        {
            map->map[j] = ft_strdup(all_file[i]);
            j++;
        }
        i++;
    }
    map->map[j] = NULL;
}
int check_line(t_map *map)
{
    int i = 0;
    while(map->map[i])
    {
        if(map->map[i][0] !=  '1' || map->map[i][ft_strlen(map->map[i])] != '1')
        return 1;
        i++;
    }
    return 0;
}