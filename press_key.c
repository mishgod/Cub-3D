/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   press_key.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:02:17 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 15:02:19 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	turn_left_right(t_all *vars, t_vect *dir, t_vect *plane)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = vars->set.rot_speed;
	if (vars->fl.right)
	{
		old_dir_x = dir->x;
		dir->x = dir->x * cos(rot_speed) - dir->y * sin(rot_speed);
		dir->y = old_dir_x * sin(rot_speed) + dir->y * cos(rot_speed);
		old_plane_x = plane->x;
		plane->x = plane->x * cos(rot_speed) - plane->y * sin(rot_speed);
		plane->y = old_plane_x * sin(rot_speed) + plane->y * cos(rot_speed);
	}
	if (vars->fl.left)
	{
		old_dir_x = dir->x;
		dir->x = dir->x * cos(-rot_speed) - dir->y * sin(-rot_speed);
		dir->y = old_dir_x * sin(-rot_speed) + dir->y * cos(-rot_speed);
		old_plane_x = plane->x;
		plane->x = plane->x * cos(-rot_speed) - plane->y * sin(-rot_speed);
		plane->y = old_plane_x * sin(-rot_speed) + plane->y * cos(-rot_speed);
	}
}

static void	forward_back(t_all *vars, double m_s)
{
	t_vect	*pos;
	t_vect	*dir;
	char	**arr;

	pos = &vars->plr.pos;
	dir = &vars->plr.dir;
	arr = vars->map.arr;
	if (vars->fl.w)
	{
		if (*(*(arr + (int)(pos->y)) + (int)(pos->x + dir->x * m_s)) != '1' \
		&& *(*(arr + (int)(pos->y)) + (int)(pos->x + dir->x * m_s)) != '2')
			pos->x += dir->x * m_s;
		if (*(*(arr + (int)(pos->y + dir->y * m_s)) + (int)(pos->x)) != '1' \
		&& *(*(arr + (int)(pos->y + dir->y * m_s)) + (int)(pos->x)) != '2')
			pos->y += dir->y * m_s;
	}
	if (vars->fl.s)
	{
		if (*(*(arr + (int)(pos->y)) + (int)(pos->x - dir->x * m_s)) != '1' \
		&& *(*(arr + (int)(pos->y)) + (int)(pos->x - dir->x * m_s)) != '2')
			pos->x -= dir->x * m_s;
		if (*(*(arr + (int)(pos->y - dir->y * m_s)) + (int)(pos->x)) != '1' \
		&& *(*(arr + (int)(pos->y - dir->y * m_s)) + (int)(pos->x)) != '2')
			pos->y -= dir->y * m_s;
	}
}

static void	go_right(t_all *vars, double m_s)
{
	double	ndir_x;
	double	ndir_y;
	t_vect	*pos;
	char	**arr;

	pos = &vars->plr.pos;
	arr = vars->map.arr;
	if (vars->fl.d)
	{
		ndir_x = -vars->plr.dir.y;
		ndir_y = vars->plr.dir.x;
		if (*(*(arr + (int)(pos->y)) + (int)(pos->x + ndir_x * m_s)) != '1' \
		&& *(*(arr + (int)(pos->y)) + (int)(pos->x + ndir_x * m_s)) != '2')
			vars->plr.pos.x += ndir_x * m_s;
		if (*(*(arr + (int)(pos->y + ndir_y * m_s)) + (int)(pos->x)) != '1' \
		&& *(*(arr + (int)(pos->y + ndir_y * m_s)) + (int)(pos->x)) != '2')
			pos->y += ndir_y * m_s;
	}
}

static void	go_left(t_all *vars, double m_s)
{
	double	ndir_x;
	double	ndir_y;
	t_vect	*pos;
	char	**arr;

	pos = &vars->plr.pos;
	arr = vars->map.arr;
	if (vars->fl.a)
	{
		ndir_x = vars->plr.dir.y;
		ndir_y = -vars->plr.dir.x;
		if (*(*(arr + (int)(pos->y)) + (int)(pos->x + ndir_x * m_s)) != '1' \
		&& *(*(arr + (int)(pos->y)) + (int)(pos->x + ndir_x * m_s)) != '2')
			vars->plr.pos.x += ndir_x * m_s;
		if (*(*(arr + (int)(pos->y + ndir_y * m_s)) + (int)(pos->x)) != '1' \
		&& *(*(arr + (int)(pos->y + ndir_y * m_s)) + (int)(pos->x)) != '2')
			pos->y += ndir_y * m_s;
	}
}

void		movement(t_all *vars)
{
	turn_left_right(vars, &vars->plr.dir, &vars->plr.plane);
	forward_back(vars, vars->set.move_speed);
	go_left(vars, vars->set.move_speed);
	go_right(vars, vars->set.move_speed);
}
