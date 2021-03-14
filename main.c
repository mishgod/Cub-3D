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

char	**map_array(t_list **map, int size)
{
	char	**map_arr;
	int		i;
	t_list	*tmp;

	map_arr = ft_calloc(size, sizeof(char*));
	i = 0;
	tmp = *map;
	while (i != size)
	{
		map_arr[i++] = tmp->line;
		tmp = tmp->next;
	}
	return (map_arr);
}

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
		draw_walls(vars, i, z_buffer);
		i++;
	}
	draw_sprites(vars, z_buffer);
	mlx_put_image_to_window(vars->mlx, vars->win, vars->img.img, 0, 0);
	return (0);
}

void	set_vars(t_all *vars)
{
	vars->tex.sprite.exist = -1;
	vars->tex.south.exist = -1;
	vars->tex.north.exist = -1;
	vars->tex.west.exist = -1;
	vars->tex.east.exist = -1;
	vars->set.exist_resol = -1;
	vars->pars.ceil.exist = -1;
	vars->pars.flr.exist = -1;
	vars->pars.num_of_params = 0;
	vars->pars.num_of_nswe = -1;
	vars->set.move_speed = 0.101;
	vars->set.rot_speed = M_PI_2 / 45;
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



void	check_map_name(char *name)
{

	while (*name != '.')
	{
		name++;
	}
	name++;
	if (ft_strncmp(name, "cub", 4))
		ft_exit("error: invalid map name");
}



int 	main(int argc, char **argv)
{
	int 	fd;
	char	*line;
	t_all	vars;

	check_map_name(argv[1]);
	vars.mlx = mlx_init();
	set_vars(&vars);
	vars.map.pointer = NULL;
	line = NULL;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		ft_exit("error: file didnt read");
	while (get_next_line(fd, &line))
		ft_lstadd_back(&vars.map.pointer, ft_lstnew(line));
	ft_lstadd_back(&vars.map.pointer, ft_lstnew(line));
	vars.map.arr = map_array(&vars.map.pointer, ft_lstsize(vars.map.pointer));
	vars.map.height = ft_lstsize(vars.map.pointer);
	mlx_get_screen_size(&vars.set.monitor.x, &vars.set.monitor.y);
	ft_parser(&vars);
	ft_valid_map(vars.map.arr, vars.pars.last_param, vars.map.height);
	//ft_free_list(vars.map.pointer);
	if (argc == 2)
		creating_window(&vars);
	if (argc == 3)
		ft_screenshot(&vars);
}

//screenshot
//makefile - libraries
//norms exe, sprites
//parser?
//на ошибки маллока
/*





        1111111111111111111111111
        1000000000110000000000001
        1011000001110000002000001
        1001220000W00000000000001
111111111011200001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10002000000000001100000010001
10000000000000000001010000001
1100000111010101111101111000111
11110111 1110101 101111010001
11111111 1111111 111111111111
 */
