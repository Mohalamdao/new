/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molamdao <molamdao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:47:55 by molamdao          #+#    #+#             */
/*   Updated: 2025/05/12 11:24:45 by molamdao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_separator(char c, char charset)
{
	if (c == charset)
		return (1);
	return (0);
}

static int	count_strings(char *str, char charset)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		while (str[i] != '\0' && check_separator(str[i], charset))
			i++;
		if (str[i] != '\0')
			count++;
		while (str[i] != '\0' && !check_separator(str[i], charset))
			i++;
	}
	return (count);
}

static char	*ft_mallocword(char *str, char charset)
{
	int		len;
	int		i;
	char	*word;

	len = 0;
	while (str[len] && !check_separator(str[len], charset))
		len++;
	i = 0;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = str[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	ft_free(char **strr)
{
	int	i;

	i = 0;
	while (strr[i])
	{
		free(strr[i]);
		i++;
	}
	free(strr);
}

char	**ft_split(char const *str, char charset)
{
	char	**strings;
	int		i;

	i = 0;
	strings = (char **)malloc(sizeof(char *) * (count_strings((char *)str,
					charset) + 1));
	if (!strings)
		return (NULL);
	while (*str != '\0')
	{
		while (*str != '\0' && check_separator(*str, charset))
			str++;
		if (*str != '\0')
		{
			strings[i] = ft_mallocword((char *)str, charset);
			if (!strings[i])
				return (ft_free(strings), NULL);
			i++;
		}
		while (*str && !check_separator(*str, charset))
			str++;
	}
	strings[i] = 0;
	return (strings);
}

/*#include <stdio.h>
int	main(int argc, char **argv)
{n
	int		index;
	char	**split;
	(void)	argc;
	split = ft_split(argv[1], argv[2]);
	index = 0;
	while (split[index])
	{
		printf("<%s>\n", split[index]);
		index++;
	}
}*/