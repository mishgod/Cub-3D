/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:35:02 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 14:35:06 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	check_all_parameters(t_all *vars)
{
	t_tex	*tex;
	t_pars	*pars;
	t_set	*set;

	tex = &vars->tex;
	pars = &vars->pars;
	set = &vars->set;
	if (tex->east.exist || tex->sprite.exist || tex->west.exist || \
	tex->south.exist || tex->north.exist || set->exist_resol || \
	pars->ceil.exist || pars->flr.exist)
		ft_exit("Error: map is invalid");
}

static void	check_nswe(int *num, int i, char **arr, int height)
{
	int		j;
	char	c;

	while (i < height - 1)
	{
		j = 0;
		while (arr[i][j])
		{
			c = arr[i][j];
			if (c == 'W' || c == 'E' || c == 'N' || c == 'S')
				(*num)++;
			j++;
		}
		i++;
	}
}

static void	check_num_of_params(t_all *vars, int i)
{
	if (vars->pars.num_of_params == 8)
	{
		vars->pars.num_of_params++;
		vars->pars.last_param = i + 1;
	}
}

static void	check_somth(t_all *vars)
{
	char	**arr;
	int		height;

	arr = vars->map.arr;
	height = vars->map.height;
	check_all_parameters(vars);
	check_nswe(&vars->pars.num_of_nswe, vars->pars.last_param + 1, arr, height);
	if (vars->pars.num_of_nswe)
		ft_exit("error: invalid map");
	while (!(vars->map.arr[vars->pars.last_param][0]))
		vars->pars.last_param++;
	if (vars->map.arr[vars->pars.last_param] == NULL)
		ft_exit("error: invalid map");
}

void		ft_parser(t_all *vars, int i, int j)
{
	while (i < vars->map.height)
	{
		j = 0;
		while (vars->map.arr[i][j] != '\0')
		{
			if (parser_resolution(vars, i, j))
				break ;
			if (parser_floor_ceilling(vars, i, j))
				break ;
			if (parcer_north_south_tex(vars, i, j))
				break ;
			if (parcer_west_east_tex(vars, i, j))
				break ;
			if (parcer_sprite_tex(vars, i, j))
				break ;
			if (vars->map.arr[i][0] == '\0')
				break ;
			if (vars->pars.num_of_params < 9)
				ft_exit("Error: invalid map");
			j++;
		}
		check_num_of_params(vars, i);
		i++;
	}
	check_somth(vars);
}
