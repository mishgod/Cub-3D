/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_floor_ceilling.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:35:37 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 14:35:40 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void	for_set_color(char *line, t_clr *clr, int j)
{
	int	i;

	i = 0;
	if (!(line))
		ft_exit("Error: invalid map");
	while (line[i])
	{
		if (!(line[i] >= '0' && line[i] <= '9'))
			ft_exit("Error: map is invalid");
		i++;
	}
	if (j == 0)
		clr->r = ft_atoi(line);
	if (j == 1)
		clr->g = ft_atoi(line);
	if (j == 2)
		clr->b = ft_atoi(line);
	clr->clr = clr->r * 65536 + clr->g * 256 + clr->b;
}

static void	set_color(char *line, t_clr *clr)
{
	char	**arr;
	int		j;

	j = 0;
	if (!(arr = ft_split(line, ',')))
		ft_exit("error: memory is not allocated");
	while (j < 3)
	{
		for_set_color(arr[j], clr, j);
		j++;
	}
	j = 0;
	while (j < 3)
		free(arr[j++]);
	free(arr);
	if (clr->r > 255 || clr->r < 0 || clr->g > 255 || \
	clr->g < 0 || clr->b > 255 || clr->b < 0)
		ft_exit("Error: map is invalid");
}

static void	check_data(char *line1, char *line2)
{
	int	j;

	j = 0;
	if (!(line1))
		ft_exit("Error: map is invalid");
	while (line2[j])
	{
		if (!((line2[j] >= '0' && line2[j] <= '9') || line2[j] <= ','))
			ft_exit("Error: map is invalid");
		j++;
	}
}

static void	parser(t_all *vars, int i, t_clr *clr, char ltr)
{
	char	*line;
	char	**arr;

	line = vars->map.arr[i];
	if (!(arr = ft_split(line, ' ')))
		ft_exit("error: memory is not allocated");
	if (arr[0][0] == ltr)
	{
		check_data(arr[0], arr[1]);
		if (arr[2])
			ft_exit("Error: map is invalid");
		set_color(arr[1], clr);
		free(arr[1]);
		free(arr[0]);
		free(arr);
	}
	else
		ft_exit("Error: map is invalid");
}

int			parser_floor_ceilling(t_all *vars, int i, int j)
{
	if (vars->map.arr[i][j] == 'F')
	{
		if (vars->map.arr[i][j + 1] == ' ')
		{
			parser(vars, i, &vars->pars.flr, 'F');
			vars->pars.flr.exist++;
			vars->pars.num_of_params++;
			return (1);
		}
		else
			ft_exit("Error: map is invalid");
	}
	if (vars->map.arr[i][j] == 'C')
	{
		if (vars->map.arr[i][j + 1] == ' ')
		{
			parser(vars, i, &vars->pars.ceil, 'C');
			vars->pars.ceil.exist++;
			vars->pars.num_of_params++;
			return (1);
		}
		else
			ft_exit("Error: map is invalid");
	}
	return (0);
}
