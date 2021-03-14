#include "../cub3d.h"

static void	put_color(t_all *vars, t_vect pos, int j, int x)
{
	int	color;

	color = my_mlx_pixel_open(vars->tex.sprite.img, (int)pos.x, (int)pos.y);
	if (color != 0)
		my_mlx_pixel_put(vars, x, j, color);
}

static void	draw_sprite(t_dspr dspr, t_all *vars, double *z_buffer)
{
	int		j;
	int		d;
	t_vect	pos;
	int		dx;

	dx = dspr.draw_start.x;
	while (dx < dspr.draw_end.x)
	{
		pos.x = (int)(256 * (dx - (-dspr.width / 2 + dspr.screen_x)) \
		* vars->tex.sprite.width / dspr.width) / 256;
		j = dspr.draw_start.y;
		if (dspr.transform.y > 0 && dx > 0 && dx < vars->set.screen_width \
		&& dspr.transform.y < *(z_buffer + dx))
		{
			pos.y = 0;
			while (j < dspr.draw_end.y)
			{
				d = j * 256 - vars->set.screen_height * 128 + dspr.height * 128;
				pos.y = ((d * vars->tex.sprite.height) / dspr.height) / 256;
				put_color(vars, pos, j, dx);
				j++;
			}
		}
		dx++;
	}
}

static void	define_draw_x_y(t_all *vars, t_dspr *dspr)
{
	dspr->draw_start.y = -dspr->height / 2 + vars->set.screen_height / 2;
	if (dspr->draw_start.y < 0)
		dspr->draw_start.y = 0;
	dspr->draw_end.y = dspr->height / 2 + vars->set.screen_height / 2;
	if (dspr->draw_end.y >= vars->set.screen_height)
		dspr->draw_end.y = vars->set.screen_height;
	dspr->width = (int)(absolute(vars->set.screen_height\
	/ dspr->transform.y * vars->coef_square));
	dspr->draw_start.x = -dspr->width / 2 + dspr->screen_x;
	if (dspr->draw_start.x < 0)
		dspr->draw_start.x = 0;
	dspr->draw_end.x = dspr->width / 2 + dspr->screen_x;
	if (dspr->draw_end.x >= vars->set.screen_width)
		dspr->draw_end.x = vars->set.screen_width;
}

void		make_proection(t_all *vars, double *z_buffer)
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
		dspr.inv_det = 1.0 / (vars->plr.plane.x * vars->plr.dir.y - \
		vars->plr.plane.y * vars->plr.dir.x);
		dspr.transform.x = dspr.inv_det * (vars->plr.dir.y * \
		dspr.sprites.x - vars->plr.dir.x * dspr.sprites.y);
		dspr.transform.y = dspr.inv_det * (-vars->plr.plane.y * \
		dspr.sprites.x + vars->plr.plane.x * dspr.sprites.y);
		dspr.screen_x = (int)((vars->set.screen_width / 2) * \
		(1 + dspr.transform.x / dspr.transform.y));
		dspr.height = (int)(absolute((vars->set.screen_height / \
		dspr.transform.y * vars->coef_square)));
		dspr.draw_start.y = -dspr.height / 2 + vars->set.screen_height / 2;
		define_draw_x_y(vars, &dspr);
		draw_sprite(dspr, vars, z_buffer);
		i++;
	}
}