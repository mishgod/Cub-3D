/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   screenshot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:02:26 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 15:02:27 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	render_one_frame(t_all *vars)
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
	return (0);
}

static void	set_headers(t_iheader *ihead, t_fheader *fhead, int h, int w)
{
	ihead->size = sizeof(*ihead);
	ihead->width = w;
	ihead->height = h;
	ihead->planes = 1;
	ihead->bit_count = 32;
	ihead->compression = 0;
	ihead->size_image = sizeof(int) * h * w;
	ihead->x_pels_per_meter = 2835;
	ihead->y_pels_per_meter = 2835;
	ihead->clr_used = 0;
	ihead->clr_important = 0;
	fhead->reserved1 = 0;
	fhead->reserved2 = 0;
	fhead->offbits = sizeof(*fhead) + ihead->size + 2;
	fhead->size = fhead->offbits + ihead->size_image;
}

static void	render_img(t_all *vars, int w, int h)
{
	t_img	*img;

	img = &vars->img;
	player_starting_position(vars, vars->map.arr);
	vars->coef_square = (double)w / (double)h / \
	(absolute(vars->plr.plane.x - vars->plr.plane.y)) / 2;
	img->img = mlx_new_image(vars->mlx, w, h);
	player_starting_position(vars, vars->map.arr);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, \
	&img->line_length, &img->endian);
	render_one_frame(vars);
}

static void	write_head(int fd, t_all *vars)
{
	t_fheader		fhead;
	t_iheader		ihead;
	unsigned short	type;
	int				h;
	int				w;

	if (fd == -1)
		ft_exit("Error: file save.bmp does not created");
	w = vars->set.screen_width;
	h = vars->set.screen_height;
	set_headers(&ihead, &fhead, h, w);
	type = 0x4d42;
	write(fd, &type, 2);
	write(fd, &fhead, sizeof(fhead));
	write(fd, &ihead, sizeof(ihead));
}

void		ft_screenshot(t_all *vars, int w, int h)
{
	int		fd;
	t_col1	col1;
	t_ivect	pos;
	int		a;

	render_img(vars, w, h);
	fd = open("save.bmp", O_CREAT | O_WRONLY | O_TRUNC, 0666);
	write_head(fd, vars);
	pos.y = h - 1;
	while (pos.y > -1)
	{
		pos.x = 0;
		while (pos.x < w)
		{
			col1.color = my_mlx_pixel_open(vars->img, pos.x, pos.y);
			write(fd, &col1, 4);
			pos.x++;
		}
		pos.y--;
	}
	a = close(fd);
	if (a == -1)
		ft_exit("Error: file save.bmp does not closed");
	ft_exit("Screenshot is created, file's name is save.bmp");
}
