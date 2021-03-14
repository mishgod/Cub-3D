/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:55:59 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 14:56:01 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	draw_textures(t_all *vars, int i, t_tex tex)
{
	int color;

	while (vars->scr.draw_start < vars->scr.draw_end)
	{
		if (vars->ray.side == 0)
		{
			if (vars->ray.dir.x > 0)
				color = my_mlx_pixel_open(tex.east.img, tex.x, tex.pos);
			else
				color = my_mlx_pixel_open(tex.west.img, tex.x, tex.pos);
		}
		else
		{
			if (vars->ray.dir.y > 0)
				color = my_mlx_pixel_open(tex.south.img, tex.x, tex.pos);
			else
				color = my_mlx_pixel_open(tex.north.img, tex.x, tex.pos);
		}
		tex.pos += vars->scr.step;
		my_mlx_pixel_put(vars, i, vars->scr.draw_start++, color);
	}
}

void		walls(t_all *vars, int i, double buf[vars->set.screen_width])
{
	walls_calculations(vars);
	draw_textures(vars, i, vars->tex);
	buf[i] = vars->ray.wall_dist;
}
