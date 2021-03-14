/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 13:59:18 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/13 13:59:20 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	set_vars(t_all *vars, int argc)
{
	vars->fl.press = 0;
	vars->fl.left = 0;
	vars->fl.right = 0;
	vars->fl.s = 0;
	vars->fl.w = 0;
	vars->fl.a = 0;
	vars->fl.d = 0;
	mlx_get_screen_size(&vars->set.monitor.x, &vars->set.monitor.y);
	vars->map.pointer = NULL;
	vars->tex.sprite.exist = -1;
	vars->tex.south.exist = -1;
	vars->tex.north.exist = -1;
	vars->tex.west.exist = -1;
	vars->tex.east.exist = -1;
	vars->set.exist_resol = -1;
	vars->pars.ceil.exist = -1;
	vars->pars.flr.exist = -1;
	vars->pars.num_of_params = 0;
	vars->pars.num_of_nswe = -1;
	vars->set.move_speed = 0.101;
	vars->set.rot_speed = M_PI_2 / 30;
	vars->set.argc = argc;
}

char	**map_array(t_list **map, int size)
{
	char	**map_arr;
	int		i;
	t_list	*tmp;

	if (!(map_arr = ft_calloc(size, sizeof(char*))))
		ft_exit("error: memory is not allocated");
	i = 0;
	tmp = *map;
	while (i != size)
	{
		map_arr[i++] = tmp->line;
		tmp = tmp->next;
	}
	return (map_arr);
}
