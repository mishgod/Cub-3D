/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_tex_coordinations.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/13 14:55:18 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/13 14:55:19 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	find_tex_x(t_all *vars, t_ray *ray, t_tex *tex)
{
	if (vars->ray.side == 0)
	{
		if (ray->dir.x > 0)
			tex->x = (int)(ray->wall_x * (double)(tex->east.width));
		else
		{
			tex->x = (int)(ray->wall_x * (double)(tex->west.width));
			tex->x = tex->west.width - tex->x - 1;
		}
	}
	else
	{
		if (ray->dir.y > 0)
		{
			tex->x = (int)(ray->wall_x * (double)(tex->south.width));
			tex->x = tex->south.width - tex->x - 1;
		}
		else
			tex->x = (int)(ray->wall_x * (double)(tex->north.width));
	}
}

static void	find_step(t_all *vars, t_ray *ray, t_scr *scr)
{
	if (vars->ray.side == 0)
	{
		if (ray->dir.x > 0)
			scr->step = 1.0 * vars->tex.east.height / scr->line_height;
		else
			scr->step = 1.0 * vars->tex.west.height / scr->line_height;
	}
	else
	{
		if (ray->dir.y > 0)
			scr->step = 1.0 * vars->tex.south.height / scr->line_height;
		else
			scr->step = 1.0 * vars->tex.north.height / scr->line_height;
	}
}

void		find_coordinations(t_all *vars)
{
	find_tex_x(vars, &vars->ray, &vars->tex);
	find_step(vars, &vars->ray, &vars->scr);
}
