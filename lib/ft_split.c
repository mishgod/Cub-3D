/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 14:33:34 by rbooker           #+#    #+#             */
/*   Updated: 2020/11/21 14:33:39 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	number_of_words(char *s, char c)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	if (s[i] == '\0')
		return (0);
	while (s[i] == c)
		i++;
	if (s[0])
		n++;
	while (s[i] != '\0')
	{
		if (s[i] != c && s[i + 1] == c)
			n++;
		i++;
	}
	if (s[i - 1] == c)
		n--;
	return (n);
}

static char	**ft_free(char **arr, int num)
{
	while (num >= 0)
	{
		free(arr[num]);
		num--;
	}
	free(arr);
	return (0);
}

char		**ft_split(char const *s, char c)
{
	int		len;
	int		i;
	char	**arr;

	i = 0;
	if (!s || !(arr = (char**)ft_calloc(number_of_words((char*)s, c) + 1,
			sizeof(char*))))
		return (0);
	if (!number_of_words((char*)s, c))
		return (arr);
	while (*s)
	{
		len = 0;
		while (*s == c && *s)
			s++;
		while (*s != c && *s)
		{
			s++;
			len++;
		}
		if (len)
			if (!(arr[i++] = ft_substr(s - len, 0, len)))
				return (ft_free(arr, i - 1));
	}
	return (arr);
}
