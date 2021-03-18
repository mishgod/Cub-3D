/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_valid_map_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:53:15 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 14:53:17 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	max_size(char *line1, char *line2)
{
	if (ft_strlen(line1) > ft_strlen(line2))
		return (ft_strlen(line2));
	else
		return (ft_strlen(line1));
}

void		check_elem_maze(char **arr, int i, int j)
{
	int	max;

	max = max_size(arr[i - 1], arr[i + 1]);
	while (arr[i][j] && j < max)
	{
		if (arr[i][j] == '0' || arr[i][j] == '2' || arr[i][j] == 'W' || \
				arr[i][j] == 'E' || arr[i][j] == 'N' || arr[i][j] == 'S')
		{
			if (arr[i - 1][j] == ' ' || arr[i + 1][j] == ' ' || \
					arr[i][j - 1] == ' ' || arr[i][j + 1] == ' ' || \
					arr[i][j + 1] == '\0')
				ft_exit("Error\nmap is invalid");
		}
		j++;
	}
	while (arr[i][j])
	{
		if (arr[i][j] == '0' || arr[i][j] == '2' || arr[i][j] == 'W' || \
				arr[i][j] == 'E' || arr[i][j] == 'N' || arr[i][j] == 'S')
			ft_exit("Error\nmap is invalid");
		j++;
	}
}
