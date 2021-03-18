/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:35:59 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 14:36:01 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		parcer_north_south_tex(t_all *vars, int i, int j)
{
	if (vars->map.arr[i][j] == 'N' && vars->map.arr[i][j + 1] == 'O')
	{
		if (vars->map.arr[i][j + 2] == ' ')
		{
			find_path(vars, i, &vars->tex.north, 'N');
			vars->tex.north.exist++;
			vars->pars.num_of_params++;
			return (1);
		}
		else
			ft_exit("Error\nmap is invalid");
	}
	if (vars->map.arr[i][j] == 'S' && vars->map.arr[i][j + 1] == 'O')
	{
		if (vars->map.arr[i][j + 2] == ' ')
		{
			find_path(vars, i, &vars->tex.south, 'S');
			vars->tex.south.exist++;
			vars->pars.num_of_params++;
			return (1);
		}
		else
			ft_exit("Error\nmap is invalid");
	}
	return (0);
}

int		parcer_west_east_tex(t_all *vars, int i, int j)
{
	if (vars->map.arr[i][j] == 'W' && vars->map.arr[i][j + 1] == 'E')
	{
		if (vars->map.arr[i][j + 2] == ' ')
		{
			find_path(vars, i, &vars->tex.west, 'W');
			vars->tex.west.exist++;
			vars->pars.num_of_params++;
			return (1);
		}
		else
			ft_exit("Error\nmap is invalid");
	}
	if (vars->map.arr[i][j] == 'E' && vars->map.arr[i][j + 1] == 'A')
	{
		if (vars->map.arr[i][j + 2] == ' ')
		{
			find_path(vars, i, &vars->tex.east, 'E');
			vars->tex.east.exist++;
			vars->pars.num_of_params++;
			return (1);
		}
		else
			ft_exit("Error\nmap is invalid");
	}
	return (0);
}

int		parcer_sprite_tex(t_all *vars, int i, int j)
{
	if (vars->map.arr[i][j] == 'S' && vars->map.arr[i][j + 1] == ' ')
	{
		find_path(vars, i, &vars->tex.sprite, 'C');
		vars->tex.sprite.exist++;
		vars->pars.num_of_params++;
		return (1);
	}
	return (0);
}
