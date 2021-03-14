/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/12 15:01:17 by rbooker           #+#    #+#             */
/*   Updated: 2021/03/12 15:01:19 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_free_spr(t_spr *spr)
{
	t_spr	*tmp;

	while (spr->next != NULL)
	{
		tmp = spr->next;
		free(spr);
		spr = NULL;
		spr = tmp;
	}
	free(spr);
	spr = NULL;
}
