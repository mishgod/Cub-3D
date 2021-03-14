/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_background.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:01:36 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 15:01:37 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_background(t_all *vars)
{
	int	y;
	int	x;

	y = 0;
	while (y < vars->set.screen_width)
	{
		x = 0;
		while (x < vars->set.screen_height / 2)
			my_mlx_pixel_put(vars, y, x++, vars->pars.ceil.clr);
		while (x < vars->set.screen_height)
			my_mlx_pixel_put(vars, y, x++, vars->pars.flr.clr);
		y++;
	}
}
