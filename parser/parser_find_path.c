/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_find_path.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:35:28 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 14:35:30 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_data(char *line1, char *line2, char ltr)
{
	if (!(line1))
		ft_exit("Error\nmap is invalid");
	if (ltr == 'C')
		if (line1[0] != 'S' || line1[1])
			ft_exit("Error\nmap is invalid");
	if (ltr == 'S')
		if (line1[0] != ltr || line1[2])
			ft_exit("Error\nmap is invalid");
	if (open(line2, O_RDONLY) == -1)
		ft_exit("Error\nmap is invalid");
}

void		find_path(t_all *vars, int i, t_side *side, char ltr)
{
	char	**arr;

	if (!(arr = ft_split(vars->map.arr[i], ' ')))
		ft_exit("Error\nmemory is not allocated");
	check_data(arr[0], arr[1], ltr);
	if (arr[2])
		ft_exit("Error\nmap is invalid");
	side->img.img = mlx_xpm_file_to_image(vars->mlx, arr[1], &side->width, \
		&side->height);
	if (side->img.img == NULL)
		ft_exit("Error\nempty xpm file");
	side->img.addr = mlx_get_data_addr(side->img.img, \
		&side->img.bits_per_pixel, &side->img.line_length, &side->img.endian);
	free(arr[1]);
	free(arr[0]);
	free(arr);
}
