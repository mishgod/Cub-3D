/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:55:01 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 14:55:03 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_spr	*ft_find_sprites(t_all *vars)
{
	int		x;
	int		y;
	t_spr	*spr1;
	int		i;

	spr1 = NULL;
	i = 0;
	y = 0;
	while (y < vars->map.height)
	{
		x = 0;
		while (*(*(vars->map.arr + y) + x))
		{
			if (*(*(vars->map.arr + y) + x) == '2')
				ft_spr_add_back(vars, &spr1, ft_spr_new(x + 0.5, y + 0.5), i++);
			x++;
		}
		y++;
	}
	return (spr1);
}

void	draw_sprites(t_all *vars, double *z_buffer)
{
	vars->spr = ft_find_sprites(vars);
	sprites_sort(vars, vars->number_of_sprites);
	make_proection(vars, z_buffer);
	ft_free_spr(vars->spr);
}
