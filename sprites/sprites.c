#include "cub3d.h"

t_spr	*ft_find_sprites(t_all *vars)
{
	int		x;
	int 	y;
	t_spr	*spr1;
	int 	i;

	spr1 = NULL;
	i = 0;
	y = 0;
	while (y < vars->map.height)
	{
		x = 0;
		while (*(*(vars->map.arr + y) + x))
		{
			if (*(*(vars->map.arr + y) + x) == '2')
				ft_spr_add_back(vars, &spr1, ft_spr_new(x + 0.5, y + 0.5), i++);
			x++;
		}
		y++;
	}
	return(spr1);
}

void	sprites_sort(t_all *vars, int n)
{
	int 	i;
	int 	j;
	int 	order[n];
	double	dist[n];
	t_spr	*spr_tmp;
	double	temp_dist;
	int 	temp_ord;
	t_spr	*point_to_strs[n];

	i = 0;
	while (i < n)
	{
		spr_tmp = ft_spr_num(vars->spr, i);
		order[i] = spr_tmp->order;
		dist[i] = spr_tmp->dist;
		i++;
	}
	i = 0;
	while (i < n) //сортировка по dist
	{
		j = n - 1;
		while (j > i)
		{
			if (dist[j - 1] > dist[j])
			{
				temp_dist = dist[j - 1];
				temp_ord = order[j - 1];
				dist[j - 1] = dist[j];
				order[j - 1] = order[j];
				dist[j] = temp_dist;
				order[j] = temp_ord;
			}
			j--;
		}
		i++;
	}
	i = 0;
	while (i < n)
	{
		point_to_strs[i] = ft_spr_num(vars->spr, order[n - 1 - i]);
		i++;
	}
	i = 0;
	spr_tmp = NULL;
	while (i < n)
	{
		ft_spr_add_new_back(vars, &spr_tmp, point_to_strs[i], i);
		i++;
	}
	ft_free_spr(vars->spr);
	vars->spr = spr_tmp;
}

void	draw_sprite(t_dspr dspr, t_all *vars, int i, double *z_buffer)
{
	int		color;
	int		j;
	t_vect	pos;

	while (dspr.draw_start.x < dspr.draw_end.x)
	{
		pos.x = (int) (256 * (dspr.draw_start.x - (-dspr.width / 2 + dspr.screen_x)) * vars->tex.sprite.width / dspr.width) / 256;
		j = dspr.draw_start.y;
		if (dspr.transform.y > 0 && dspr.draw_start.x > 0 && dspr.draw_start.x < vars->set.screen_width && dspr.transform.y < *(z_buffer + dspr.draw_start.x))
		{
			pos.y = 0;
			while (j < dspr.draw_end.y)
			{
				int d = j * 256 - vars->set.screen_height * 128 + dspr.height * 128;
				pos.y = ((d * vars->tex.sprite.height) / dspr.height) / 256;
				color = my_mlx_pixel_open(vars->tex.sprite.img, pos.x, pos.y);
				if (color != 0)
					my_mlx_pixel_put(vars, dspr.draw_start.x, j, color);
				j++;
			}
		}
		dspr.draw_start.x++;
	}
}

void	make_proection(t_all *vars, double *z_buffer)
{
	t_dspr	dspr;
	t_spr	*tmp;
	int		i;

	i = 0;
	while (i < vars->number_of_sprites)
	{
		tmp = ft_spr_num(vars->spr, i);
		dspr.sprites.x = tmp->pos.x - vars->plr.pos.x;
		dspr.sprites.y = tmp->pos.y - vars->plr.pos.y;
		dspr.inv_det = 1.0 / (vars->plr.plane.x * vars->plr.dir.y - vars->plr.plane.y * vars->plr.dir.x);
		dspr.transform.x = dspr.inv_det * (vars->plr.dir.y * dspr.sprites.x - vars->plr.dir.x * dspr.sprites.y);
		dspr.transform.y = dspr.inv_det * (-vars->plr.plane.y * dspr.sprites.x + vars->plr.plane.x * dspr.sprites.y);
		dspr.screen_x = (int) ((vars->set.screen_width / 2) * (1 + dspr.transform.x / dspr.transform.y));
		dspr.height = (int) (absolute((vars->set.screen_height / dspr.transform.y * vars->coef_square)));
		dspr.draw_start.y = -dspr.height / 2 + vars->set.screen_height / 2;
		if (dspr.draw_start.y < 0)
			dspr.draw_start.y = 0;
		dspr.draw_end.y = dspr.height / 2 + vars->set.screen_height / 2;
		if (dspr.draw_end.y >= vars->set.screen_height)
			dspr.draw_end.y = vars->set.screen_height - 1;
		dspr.width = (int) (absolute(vars->set.screen_height / dspr.transform.y * vars->coef_square));
		dspr.draw_start.x = -dspr.width / 2 + dspr.screen_x;
		if (dspr.draw_start.x < 0)
			dspr.draw_start.x = 0;
		dspr.draw_end.x = dspr.width / 2 + dspr.screen_x;
		if (dspr.draw_end.x >= vars->set.screen_width)
			dspr.draw_end.x = vars->set.screen_width - 1;
		draw_sprite(dspr, vars, i, z_buffer);
		i++;
	}
}

void 	draw_sprites(t_all *vars, double *z_buffer)
{
	vars->spr = ft_find_sprites(vars);
	sprites_sort(vars, vars->number_of_sprites);
	make_proection(vars, z_buffer);
	ft_free_spr(vars->spr);
}