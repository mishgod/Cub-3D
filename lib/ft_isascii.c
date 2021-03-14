/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:48:59 by rbooker           #+#    #+#             */
/*   Updated: 2020/10/29 19:49:59 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isascii(int c)
{
	int		i;

	i = 0;
	if (c >= 0 && c <= 127)
		return (1);
	else
		return (0);
}
