/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_minilibx_utils_2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahamza <ahamza@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 21:44:46 by ahamza            #+#    #+#             */
/*   Updated: 2025/08/24 21:44:47 by ahamza           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_strafe_left(int k)
{
	return (k == 97 || k == 65);
}

int	is_strafe_right(int k)
{
	return (k == 100 || k == 68);
}

int	is_rot_left(int k)
{
	return (k == 65361);
}

int	is_rot_right(int k)
{
	return (k == 65363);
}
