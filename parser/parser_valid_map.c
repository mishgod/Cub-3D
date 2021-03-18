/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:36:08 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 14:36:10 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_first_last_line(char *line0, char *line_n)
{
	int i;

	i = 0;
	while (line0[i])
	{
		if (line0[i] != '1' && line0[i] != ' ')
			ft_exit("Error\nmap is invalid");
		i++;
	}
	i = 0;
	while (line_n[i])
	{
		if (line_n[i] != '1' && line_n[i] != ' ')
			ft_exit("Error\nmap is invalid");
		i++;
	}
}

static void	check_borders(char **arr, int i, int height)
{
	while (i < height - 1)
	{
		if (arr[i][0] != '1' && arr[i][0] != ' ')
			ft_exit("Error\nmap is invalid");
		if (arr[i][ft_strlen(arr[i]) - 1] != '1' && \
			arr[i][ft_strlen(arr[i]) - 1] != ' ')
			ft_exit("Error\nmap is invalid");
		i++;
	}
}

void		check_trash(char **arr, int height, int n)
{
	int		j;
	char	c;

	while (n < height)
	{
		j = 0;
		while (arr[n][j])
		{
			c = arr[n][j];
			if (c != '1' && c != ' ' && c != '0' && c != 'W' && \
			c != 'E' && c != 'S' && c != 'N' && c != '2')
				ft_exit("Error\ninvalid map - trash");
			j++;
		}
		n++;
	}
}

static void	check_maze(char **arr, int height, int i)
{
	int	j;

	while (i < height - 1)
	{
		j = 1;
		check_elem_maze(arr, i, j);
		i++;
	}
}

void		ft_valid_map(char **arr, int n, int height)
{
	check_trash(arr, height, n);
	check_first_last_line(arr[n], arr[height - 1]);
	check_borders(arr, n, height);
	check_maze(arr, height, n + 1);
}
