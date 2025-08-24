/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:45:02 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 21:45:03 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int ac, char **av)
{
	t_cub3d	cub;
	char	**file_content;

	file_content = NULL;
	if (ac != 2)
	{
		printf("error arg\n");
		return (1);
	}
	file_content = content_file(av[1], 0);
	if (!file_content)
	{
		printf("Error: Cannot read file\n");
		return (1);
	}
	initialization_struct(&cub, file_content, 0, 0);
	if (parsing(&cub) == 1)
		return (printf("Error: Map parsing failed\n"), 1);
	if (check_rgb_text(cub) == 1)
		printf("Warning: Some textures/colors invalid, using defaults\n");
	init_player_direction(&cub);
	init_minilibx(&cub);
	return (0);
}
