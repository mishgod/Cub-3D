/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:02:32 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 15:02:33 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	absolute(double num)
{
	if (num < 0)
		num *= -1;
	return (num);
}

int		closed(t_all *vars)
{
	free(vars->map.arr);
	mlx_destroy_image(vars->mlx, vars->img.img);
	mlx_destroy_image(vars->mlx, vars->tex.west.img.img);
	mlx_destroy_window(vars->mlx, vars->win);
	exit(0);
}

void	my_mlx_pixel_put(t_all *vars, int x, int y, int color)
{
	char	*dst;
	t_img	*img;

	img = &vars->img;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		my_mlx_pixel_open(t_img data, int x, int y)
{
	char *dst;

	dst = data.addr + (y * data.line_length + x * (data.bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

void	ft_exit(char *line)
{
	int	i;

	i = ft_strlen(line);
	write(1, line, i);
	write(1, "\n", 1);
	exit(0);
}
