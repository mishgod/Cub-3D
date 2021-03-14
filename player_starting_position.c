/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_starting_position.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:02:02 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 15:02:07 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_west_and_east(t_all *vars, int x, int y)
{
	if (*(*(vars->map.arr + y) + x) == 'W')
	{
		vars->plr.dir.x = -1;
		vars->plr.dir.y = 0;
		vars->plr.plane.x = 0;
		vars->plr.plane.y = -0.66;
	}
	if (*(*(vars->map.arr + y) + x) == 'E')
	{
		vars->plr.dir.x = 1;
		vars->plr.dir.y = 0;
		vars->plr.plane.x = 0;
		vars->plr.plane.y = 0.66;
	}
}

static void	check_north_and_south(t_all *vars, int x, int y)
{
	if (*(*(vars->map.arr + y) + x) == 'S')
	{
		vars->plr.dir.x = 0;
		vars->plr.dir.y = 1;
		vars->plr.plane.x = -0.66;
		vars->plr.plane.y = 0;
	}
	if (*(*(vars->map.arr + y) + x) == 'N')
	{
		vars->plr.dir.x = 0;
		vars->plr.dir.y = -1;
		vars->plr.plane.x = 0.66;
		vars->plr.plane.y = 0;
	}
}

static void	number_of_sprites(t_all *vars, int x, int y)
{
	if (*(*(vars->map.arr + y) + x) == '2')
		vars->number_of_sprites++;
}

void		player_starting_position(t_all *vars, char **arr)
{
	int		x;
	int		y;

	y = 0;
	vars->number_of_sprites = 0;
	while (y < vars->map.height)
	{
		x = 0;
		while (*(*(vars->map.arr + y) + x))
		{
			number_of_sprites(vars, x, y);
			if (*(*(arr + y) + x) == 'N' || *(*(arr + y) + x) == 'S'\
			|| *(*(arr + y) + x) == 'W' || *(*(arr + y) + x) == 'E')
			{
				vars->plr.pos.x = x + 0.5;
				vars->plr.pos.y = y + 0.5;
				check_north_and_south(vars, x, y);
				check_west_and_east(vars, x, y);
			}
			x++;
		}
		y++;
	}
}
