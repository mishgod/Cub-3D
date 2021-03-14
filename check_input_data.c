/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 18:14:41 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 18:14:42 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	check_map_name(char *name)
{
	while (*name != '.')
	{
		name++;
	}
	name++;
	if (ft_strncmp(name, "cub", 4))
		ft_exit("error: invalid map name");
}

static void	check_third_param(char *line)
{
	if (ft_strncmp(line, "--save", 6))
		ft_exit("error: wrong second parameter");
}

void		check_input_data(int argc, char **argv)
{
	if (argc == 1)
		ft_exit("error: no map");
	check_map_name(argv[1]);
	if (argc == 3)
		check_third_param(argv[2]);
	if (argc > 3)
		ft_exit("error: a lot of parameters");
}
