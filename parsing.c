/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:45:50 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 21:45:51 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_around(t_cub3d *cub, int i, int j)
{
	if (!cub->map[i][j + 1] || !cub->map[i][j - 1]
		|| !cub->map[i + 1][j] || !cub->map[i - 1][j]
		|| cub->map[i][j + 1] == ' ' || cub->map[i][j - 1] == ' '
		|| cub->map[i + 1][j] == ' ' || cub->map[i - 1][j] == ' ')
		return (1);
	return (0);
}

int	check_outline(t_cub3d *cub)
{
	int	i;
	int	j;

	i = -1;
	while (cub->map[++i])
	{
		j = 0;
		while (cub->map[i][j] == ' ' || cub->map[i][j] == '\t')
			j++;
		if (cub->map[i][j] != '1')
			return (1);
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '0' && check_around(cub, i, j) == 1)
			{
				printf("Error : invalid blank space \n");
				return (1);
			}
			j++;
		}
	}
	return (0);
}

int	check_element_map(t_cub3d *cub, int i, int j)
{
	if (cub->map[0] == NULL)
	{
		printf("Error : You have to put a map\n");
		return (1);
	}
	while (cub->map[++i])
	{
		j = -1;
		if (cub->map[i][0] == '\0')
		{
			printf("Error : empty line in the map\n");
			return (1);
		}
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] != '1' && cub->map[i][j] != '0'
				&& cub->map[i][j] != 'N' && cub->map[i][j] != 'E'
				&& cub->map[i][j] != 'S' && cub->map[i][j] != 'W'
				&& cub->map[i][j] != ' ')
				return (printf("Error: unauthorized elements\n"), 1);
		}
	}
	return (0);
}

int	pos_player(t_cub3d *cub, int i, int j)
{
	cub->count = 0;
	cub->width = 0;
	while (cub->map[++i])
	{
		j = -1;
		while (cub->map[i][++j])
		{
			if (cub->map[i][j] == 'N' || cub->map[i][j] == 'E'
				|| cub->map[i][j] == 'S' || cub->map[i][j] == 'W')
			{
				cub->count++;
				cub->pos_i_player = i;
				cub->pos_j_player = j;
				cub->orientation = cub->map[i][j];
				cub->map[i][j] = '0';
			}
		}
		if (j > cub->width)
			cub->width = j;
	}
	cub->height = i;
	if (cub->count != 1)
		return (1);
	return (0);
}

int	parsing(t_cub3d *cub)
{
	if (!cub->ceiling || !cub->ea_text || !cub->floor
		|| !cub->no_text || !cub->so_text || !cub->we_text)
	{
		printf("Error : The file content is not correct\n");
		return (1);
	}
	if (check_element_map(cub, -1, -1) == 1)
		return (1);
	if (check_outline(cub) == 1)
	{
		printf("Error : The map is not valid \n");
		return (1);
	}
	if (pos_player(cub, -1, -1) == 1)
	{
		printf("Error : there must be 1 player \n");
		return (1);
	}
	return (0);
}
