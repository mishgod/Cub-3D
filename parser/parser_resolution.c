/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:35:47 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 14:35:51 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	find_screen_side(char *line)
{
	int j;
	int side;

	j = 0;
	while (line[j])
	{
		if (!(line[j] >= '0' && line[j] <= '9'))
			ft_exit("Error: map is invalid");
		j++;
	}
	side = ft_atoi(line);
	if (side < 1)
		ft_exit("Error: map is invalid");
	return (side);
}

static void	free_arr(char **arr, int n)
{
	int i;

	i = 0;
	while (i < n)
		free(arr[i++]);
	free(arr);
}

static void	parser(t_all *vars, int i)
{
	char	**arr;

	if (!(arr = ft_split(vars->map.arr[i], ' ')))
		ft_exit("error: memory is not allocated");
	if (arr[0][0] == 'R')
	{
		if (!(arr[1]))
			ft_exit("Error: map is invalid");
		if (!(arr[2]))
			ft_exit("Error: map is invalid");
		vars->set.screen_width = find_screen_side(arr[1]);
		vars->set.screen_height = find_screen_side(arr[2]);
		if (arr[3])
			ft_exit("Error: map is invalid");
		free_arr(arr, 3);
	}
	else
		ft_exit("Error: map is invalid");
}

static void	change_resolution(t_all *vars)
{
	if (vars->set.argc == 2)
	{
		if (vars->set.screen_width > vars->set.monitor.x)
			vars->set.screen_width = vars->set.monitor.x;
		if (vars->set.screen_height > vars->set.monitor.y)
			vars->set.screen_height = vars->set.monitor.y;
	}
	if (vars->set.argc == 3)
	{
		if (vars->set.screen_width > 16000)
			vars->set.screen_width = 16000;
		if (vars->set.screen_height > 16000)
			vars->set.screen_height = 16000;
	}
}

int			parser_resolution(t_all *vars, int i, int j)
{
	if (vars->map.arr[i][j] == 'R')
	{
		if (vars->map.arr[i][j + 1] == ' ')
		{
			parser(vars, i);
			change_resolution(vars);
			vars->set.exist_resol++;
			vars->pars.num_of_params++;
			return (1);
		}
		else
			ft_exit("Error: map is invalid");
	}
	return (0);
}
