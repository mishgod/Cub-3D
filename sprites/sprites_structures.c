#include "cub3d.h"

t_spr	*ft_spr_new(double x, double y)
{
	t_spr	*new;

	new = malloc(sizeof(t_spr));
	new->pos.x = x;
	new->pos.y = y;
	new->next = NULL;
	return (new);
}

t_spr	*ft_spr_last(t_spr *spr)
{
	if (spr == NULL)
		return (NULL);
	while (spr->next)
		spr = spr->next;
	return (spr);
}

t_spr	*ft_spr_num(t_spr *spr, int n) //n начинается с 0
{
	int	i;

	i = 0;
	while (i < n)
	{
		spr = spr->next;
		i++;
	}
	return (spr);
}

void	ft_spr_add_back(t_all *vars, t_spr **spr, t_spr *new, int i)
{
	t_spr *last;

	if ((*spr) != NULL)
	{
		last = ft_spr_last(*spr);
		last->next = new;
	}
	else
		*spr = new;
	new->order = i;
	new->dist = (vars->plr.pos.x - new->pos.x) * (vars->plr.pos.x - new->pos.x) + (vars->plr.pos.y - new->pos.y) * (vars->plr.pos.y - new->pos.y);
}

void	ft_spr_add_new_back(t_all *vars, t_spr **spr, t_spr *new, int i)
{
	t_spr *last;
	t_spr *new_spr;

	new_spr = ft_spr_new(0, 0);
	if ((*spr) != NULL)
	{
		last = ft_spr_last(*spr);
		last->next = new_spr;
		new_spr->pos.x = new->pos.x;
		new_spr->pos.y = new->pos.y;
		new_spr->order = i;
		new_spr->dist = new->dist;
		new_spr->next = NULL;
	}
	else
	{
		*spr = new_spr;
		new_spr->pos.x = new->pos.x;
		new_spr->pos.y = new->pos.y;
		new_spr->order = i;
		new_spr->dist = new->dist;
		new_spr->next = NULL;
	}
}