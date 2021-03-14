/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:01:27 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 15:01:29 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		render_frame(t_all *vars)
{
	int		i;
	double	z_buffer[vars->set.screen_width];

	ft_background(vars);
	i = 0;
	while (i < vars->set.screen_width)
	{
		vars->plr.cam = 2 * i / (double)vars->set.screen_width - 1;
		vars->ray.dir.x = vars->plr.dir.x + vars->plr.plane.x * vars->plr.cam;
		vars->ray.dir.y = vars->plr.dir.y + vars->plr.plane.y * vars->plr.cam;
		vars->map.x = (int)vars->plr.pos.x;
		vars->map.y = (int)vars->plr.pos.y;
		vars->ray.delta_dist.x = absolute(1 / vars->ray.dir.x);
		vars->ray.delta_dist.y = absolute(1 / vars->ray.dir.y);
		walls(vars, i, z_buffer);
		i++;
	}
	draw_sprites(vars, z_buffer);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

void	creating_window(t_all *vars)
{
	int		w;
	int		h;
	t_img	*img;
	t_vect	*pl;

	img = &vars->img;
	pl = &vars->plr.plane;
	w = vars->set.screen_width;
	h = vars->set.screen_height;
	player_starting_position(vars, vars->map.arr);
	vars->coef_square = (double)w / (double)h / (absolute(pl->x - pl->y)) / 2;
	vars->win = mlx_new_window(vars->mlx, w, h, "cub3d");
	img->img = mlx_new_image(vars->mlx, w, h);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
	mlx_hook(vars->win, 2, 1L << 0, press_key, vars);
	mlx_hook(vars->win, 17, 1L << 0, closed, vars);
	mlx_loop_hook(vars->mlx, render_frame, vars);
	mlx_loop(vars->mlx);
}

int		main(int argc, char **argv)
{
	int		fd;
	char	*line;
	t_all	vars;

	line = NULL;
	check_input_data(argc, argv);
	set_vars(&vars, argc);
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit("error: file didnt read");
	vars.mlx = mlx_init();
	while (get_next_line(fd, &line))
		ft_lstadd_back(&vars.map.pointer, ft_lstnew(line));
	ft_lstadd_back(&vars.map.pointer, ft_lstnew(line));
	if (vars.map.pointer == NULL)
		ft_exit("Error: empty map");
	vars.map.arr = map_array(&vars.map.pointer, ft_lstsize(vars.map.pointer));
	vars.map.height = ft_lstsize(vars.map.pointer);
	ft_parser(&vars, 0, 0);
	ft_valid_map(vars.map.arr, vars.pars.last_param, vars.map.height);
	if (argc == 2)
		creating_window(&vars);
	if (argc == 3)
		ft_screenshot(&vars, vars.set.screen_width, vars.set.screen_height);
}
