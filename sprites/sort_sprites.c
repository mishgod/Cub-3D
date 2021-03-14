/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_sprites.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 16:52:24 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 16:52:26 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static void		bubble_sort(int n, double dist[n], int order[n])
{
	int		i;
	int		j;
	double	temp_dist;
	int		temp_ord;

	i = 0;
	while (i < n)
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
}

static void		sort_lines(int n, t_all *vars, t_spr *p_to_s[n], int order[n])
{
	int	i;

	i = 0;
	while (i < n)
	{
		p_to_s[i] = ft_spr_num(vars->spr, order[n - 1 - i]);
		i++;
	}
}

static t_spr	*make_new_srt(t_spr *spr_tmp, int n, t_spr *p_to_s[n])
{
	int	i;

	i = 0;
	spr_tmp = NULL;
	while (i < n)
	{
		ft_spr_add_new_back(&spr_tmp, p_to_s[i], i);
		i++;
	}
	return (spr_tmp);
}

void			sprites_sort(t_all *vars, int n)
{
	int		i;
	int		order[n];
	double	dist[n];
	t_spr	*spr_tmp;
	t_spr	*point_to_strs[n];

	i = 0;
	while (i < n)
	{
		spr_tmp = ft_spr_num(vars->spr, i);
		order[i] = spr_tmp->order;
		dist[i] = spr_tmp->dist;
		i++;
	}
	bubble_sort(n, dist, order);
	sort_lines(n, vars, point_to_strs, order);
	spr_tmp = make_new_srt(spr_tmp, n, point_to_strs);
	ft_free_spr(vars->spr);
	vars->spr = spr_tmp;
}
