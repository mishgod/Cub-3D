/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_structures.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 14:55:09 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 14:55:11 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_spr	*ft_spr_new(double x, double y)
{
	t_spr	*new;

	if (!(new = ft_calloc(1, sizeof(t_spr))))
		ft_exit("Error\nmemory is not allocated");
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

t_spr	*ft_spr_num(t_spr *spr, int n)
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
	t_spr	*last;
	t_vect	*pos;

	pos = &vars->plr.pos;
	if ((*spr) != NULL)
	{
		last = ft_spr_last(*spr);
		last->next = new;
	}
	else
		*spr = new;
	new->order = i;
	new->dist = (pos->x - new->pos.x) * (pos->x - new->pos.x) + \
	(pos->y - new->pos.y) * (pos->y - new->pos.y);
}

void	ft_spr_add_new_back(t_spr **spr, t_spr *new, int i)
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
