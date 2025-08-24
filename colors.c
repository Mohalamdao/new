/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:44:22 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 21:44:23 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	parse_rgb_string(char *rgb_str)
{
	char	**rgb_parts;
	int		r;
	int		g;
	int		b;
	int		color;

	if (!rgb_str)
		return (0x000000);
	rgb_parts = ft_split(rgb_str, ',');
	if (!rgb_parts || !rgb_parts[0] || !rgb_parts[1] || !rgb_parts[2])
		return (0x000000);
	r = ft_atoi(rgb_parts[0]);
	g = ft_atoi(rgb_parts[1]);
	b = ft_atoi(rgb_parts[2]);
	color = (r << 16) | (g << 8) | b;
	free(rgb_parts[0]);
	free(rgb_parts[1]);
	free(rgb_parts[2]);
	free(rgb_parts);
	return (color);
}

void	init_colors(t_cub3d *cub, int *floor_color, int *ceiling_color)
{
	*floor_color = parse_rgb_string(cub->floor);
	*ceiling_color = parse_rgb_string(cub->ceiling);
}
