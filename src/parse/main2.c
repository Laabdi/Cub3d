/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moaregra <moaregra@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 12:38:48 by moaregra          #+#    #+#             */
/*   Updated: 2025/01/22 13:30:28 by moaregra         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/cube3d.h"

int	main(int ac, char **av)
{
	t_map map;

	// Initialize the structure to zero
	ft_memset(&map, 0, sizeof(t_map));

	if (ac != 2)
		return ((write(2, "invalid number of parametres\n", 30)), 1);

	/* function to check if the file passed as parametre exists;
		if the file type is compatible with the subjects
		*/
	if (check_file_name(av[1]) == 0)
		return ((write(2, "file invalid\n", 14)), 1);

	fill_struct(&map, av[1]); // Note: passing address of map

	printf("%s\n", map.no);
	printf("%s\n", map.se);
	printf("%s\n", map.ea);
	printf("%s\n", map.we);
	/*
		check floor and celling texture
		every number should be in range of 0 to 255(both included)
		*/

	if (check_texture(map) == 0)
		return ((write(2, "invalid floor or celling texture\n", 34)), 1);
	/*
		check if the map is valid no hole in the map and the player
		that means the players exists and the map is fully surronded
		by walls
		*/
	// if (check_map(map) == 0)
	//     return ((write(2, "invalid map\n", 13)), 1);

	return (0);
}