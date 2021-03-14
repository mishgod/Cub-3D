/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   walls_calculations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:57:30 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 14:57:33 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	find_the_side_dist(t_all *vars, t_ray *ray, t_vect *pos)
{
	if (ray->dir.x < 0)
	{
		ray->step.x = -1;
		ray->side_dist.x = (-vars->map.x + pos->x) * ray->delta_dist.x;
	}
	else
	{
		ray->step.x = 1;
		ray->side_dist.x = (vars->map.x + 1.0 - pos->x) * ray->delta_dist.x;
	}
	if (ray->dir.y < 0)
	{
		ray->step.y = -1;
		ray->side_dist.y = (-vars->map.y + pos->y) * ray->delta_dist.y;
	}
	else
	{
		ray->step.y = 1;
		ray->side_dist.y = (vars->map.y + 1.0 - pos->y) * ray->delta_dist.y;
	}
}

static void	find_the_hitting(t_all *vars)
{
	int	hit;

	hit = 0;
	while (hit == 0)
	{
		if (vars->ray.side_dist.x < vars->ray.side_dist.y)
		{
			vars->ray.side_dist.x += vars->ray.delta_dist.x;
			vars->map.x += vars->ray.step.x;
			vars->ray.side = 0;
		}
		else
		{
			vars->ray.side_dist.y += vars->ray.delta_dist.y;
			vars->map.y += vars->ray.step.y;
			vars->ray.side = 1;
		}
		if (*(*(vars->map.arr + vars->map.y) + vars->map.x) == '1')
			hit = 1;
	}
}

static void	find_height_v_line(t_all *vars, t_vect pos, t_ray *ray, t_scr *scr)
{
	int		h;
	t_ivect map;

	map.x = vars->map.x;
	map.y = vars->map.y;
	h = vars->set.screen_height;
	if (vars->ray.side == 0)
		ray->wall_dist = (map.x - pos.x + (1 - ray->step.x) / 2) / ray->dir.x;
	else
		ray->wall_dist = (map.y - pos.y + (1 - ray->step.y) / 2) / ray->dir.y;
	scr->line_height = (int)(h / ray->wall_dist * vars->coef_square);
	if (scr->line_height < 0)
		scr->line_height = 3000;
	scr->draw_start = -scr->line_height / 2 + h / 2;
	if (scr->draw_start < 0)
		scr->draw_start = 0;
	scr->draw_end = scr->line_height / 2 + h / 2;
	if (scr->draw_end >= h)
		scr->draw_end = h;
}

void		walls_calculations(t_all *vars)
{
	t_ray	*ray;

	ray = &vars->ray;
	find_the_side_dist(vars, &vars->ray, &vars->plr.pos);
	find_the_hitting(vars);
	find_height_v_line(vars, vars->plr.pos, &vars->ray, &vars->scr);
	if (ray->side == 0)
		ray->wall_x = vars->plr.pos.y + ray->wall_dist * ray->dir.y;
	else
		ray->wall_x = vars->plr.pos.x + ray->wall_dist * ray->dir.x;
	ray->wall_x -= floor(ray->wall_x);
	find_coordinations(vars);
	vars->tex.pos = (vars->scr.draw_start - vars->set.screen_height / 2 + \
		vars->scr.line_height / 2) * vars->scr.step;
}
