/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/29 19:35:36 by rbooker           #+#    #+#             */
/*   Updated: 2020/10/29 19:36:26 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isdigit(int c)
{
	int		i;

	i = 0;
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
