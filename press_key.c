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

static void	turn_left_right(int code, t_all *vars, t_vect *dir, t_vect *plane)
{
	double	old_dir_x;
	double	old_plane_x;
	double	rot_speed;

	rot_speed = vars->set.rot_speed;
	if (code == 124)
	{
		old_dir_x = dir->x;
		dir->x = dir->x * cos(rot_speed) - dir->y * sin(rot_speed);
		dir->y = old_dir_x * sin(rot_speed) + dir->y * cos(rot_speed);
		old_plane_x = plane->x;
		plane->x = plane->x * cos(rot_speed) - plane->y * sin(rot_speed);
		plane->y = old_plane_x * sin(rot_speed) + plane->y * cos(rot_speed);
	}
	if (code == 123)
	{
		old_dir_x = dir->x;
		dir->x = dir->x * cos(-rot_speed) - dir->y * sin(-rot_speed);
		dir->y = old_dir_x * sin(-rot_speed) + dir->y * cos(-rot_speed);
		old_plane_x = plane->x;
		plane->x = plane->x * cos(-rot_speed) - plane->y * sin(-rot_speed);
		plane->y = old_plane_x * sin(-rot_speed) + plane->y * cos(-rot_speed);
	}
}

static void	forward_back(int code, t_all *vars, double m_s)
{
	t_vect	*pos;
	t_vect	*dir;
	char	**arr;

	pos = &vars->plr.pos;
	dir = &vars->plr.dir;
	arr = vars->map.arr;
	if (code == 126 || code == 13)
	{
		if (*(*(arr + (int)(pos->y)) + (int)(pos->x + dir->x * m_s)) != '1' \
		&& *(*(arr + (int)(pos->y)) + (int)(pos->x + dir->x * m_s)) != '2')
			pos->x += dir->x * m_s;
		if (*(*(arr + (int)(pos->y + dir->y * m_s)) + (int)(pos->x)) != '1' \
		&& *(*(arr + (int)(pos->y + dir->y * m_s)) + (int)(pos->x)) != '2')
			pos->y += dir->y * m_s;
	}
	if (code == 125 || code == 1)
	{
		if (*(*(arr + (int)(pos->y)) + (int)(pos->x - dir->x * m_s)) != '1' \
		&& *(*(arr + (int)(pos->y)) + (int)(pos->x - dir->x * m_s)) != '2')
			pos->x -= dir->x * m_s;
		if (*(*(arr + (int)(pos->y - dir->y * m_s)) + (int)(pos->x)) != '1' \
		&& *(*(arr + (int)(pos->y - dir->y * m_s)) + (int)(pos->x)) != '2')
			pos->y -= dir->y * m_s;
	}
}

static void	go_right(int keycode, t_all *vars, double m_s)
{
	double	ndir_x;
	double	ndir_y;
	t_vect	*pos;
	char	**arr;

	pos = &vars->plr.pos;
	arr = vars->map.arr;
	if (keycode == 2)
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

static void	go_left(int keycode, t_all *vars, double m_s)
{
	double	ndir_x;
	double	ndir_y;
	t_vect	*pos;
	char	**arr;

	pos = &vars->plr.pos;
	arr = vars->map.arr;
	if (keycode == 0)
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

int			press_key(int keycode, t_all *vars)
{
	if (keycode == 53)
		closed(vars);
	turn_left_right(keycode, vars, &vars->plr.dir, &vars->plr.plane);
	forward_back(keycode, vars, vars->set.move_speed);
	go_left(keycode, vars, vars->set.move_speed);
	go_right(keycode, vars, vars->set.move_speed);
	return (0);
}
