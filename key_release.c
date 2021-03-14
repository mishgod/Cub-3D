/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_release.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/14 19:30:30 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/14 19:30:32 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_release(int keycode, t_all *vars)
{
	vars->fl.press = 0;
	if (keycode == 123)
		vars->fl.left = 0;
	if (keycode == 124)
		vars->fl.right = 0;
	if (keycode == 125 || keycode == 1)
		vars->fl.s = 0;
	if (keycode == 126 || keycode == 13)
		vars->fl.w = 0;
	if (keycode == 0)
		vars->fl.a = 0;
	if (keycode == 2)
		vars->fl.d = 0;
	return (0);
}

int		key_press(int keycode, t_all *vars)
{
	vars->fl.press = 1;
	if (keycode == 123)
		vars->fl.left = 1;
	if (keycode == 124)
		vars->fl.right = 1;
	if (keycode == 125 || keycode == 1)
		vars->fl.s = 1;
	if (keycode == 126 || keycode == 13)
		vars->fl.w = 1;
	if (keycode == 0)
		vars->fl.a = 1;
	if (keycode == 2)
		vars->fl.d = 1;
	if (keycode == 53)
		closed(vars);
	return (0);
}
