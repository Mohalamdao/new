/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molamdao <molamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/12 10:47:47 by molamdao          #+#    #+#             */
/*   Updated: 2025/08/24 14:55:44 by molamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	strip_newline(char *line)
{
	int	len;

	len = strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = '\0';
}

char	**content_file(char *file, int count)
{
	char	**map;
	int		fd;
	char	*line;
	char	**new_map;

	map = NULL;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		return (NULL);
	line = get_next_line(fd);
	while (line)
	{
		strip_newline(line);
		new_map = realloc(map, sizeof(char *) * (count + 2));
		if (!new_map)
			return (NULL);
		map = new_map;
		map[count] = line;
		count++;
		map[count] = NULL;
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}

int	count_map_lines(char **file_content, int start_index)
{
	int	count;

	count = 0;
	while (file_content[start_index])
	{
		count++;
		start_index++;
	}
	return (count);
}

static void	set_texture_color(t_cub3d *cub, char *line)
{
	if (strncmp(line, "NO", 2) == 0)
		cub->NO_text = skip_space(line + 3);
	else if (strncmp(line, "SO", 2) == 0)
		cub->SO_text = skip_space(line + 3);
	else if (strncmp(line, "EA", 2) == 0)
		cub->EA_text = skip_space(line + 3);
	else if (strncmp(line, "WE", 2) == 0)
		cub->WE_text = skip_space(line + 3);
	else if (strncmp(line, "F", 1) == 0)
		cub->floor = skip_space(line + 2);
	else if (strncmp(line, "C", 1) == 0)
		cub->ceiling = skip_space(line + 2);
}

void	initialization_struct(t_cub3d *cub, char **file_content, int i, int j)
{
	char	*line;

	while (file_content[i])
	{
		line = skip_space(file_content[i]);
		if (line[0] != '\0')
		{
			set_texture_color(cub, line);
			if (line[0] != 'N' && line[0] != 'S' && line[0] != 'E'
				&& line[0] != 'W' && line[0] != 'F' && line[0] != 'C')
				break ;
		}
		i++;
	}
	cub->map = malloc(sizeof(char *) * (count_map_lines(file_content, i) + 1));
	while (file_content[i])
	{
		cub->map[j] = ft_strdup(file_content[i]);
		i++;
		j++;
	}
	cub->map[j] = NULL;
}
