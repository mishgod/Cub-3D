/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbooker <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/04 14:35:13 by rbooker           #+#    #+#             */
/*   Updated: 2020/12/04 14:35:16 by rbooker          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int	ft_free(char **buf)
{
	free(*buf);
	*buf = NULL;
	return (0);
}

static char	*ft_remainder(char *buf, int i)
{
	int j;

	j = 0;
	while (buf[i])
		buf[j++] = buf[i++];
	buf[j] = '\0';
	return (buf);
}

static char	*ft_join(char **line, char *buf, int len_buf)
{
	char	*newline;
	int		len_line;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len_line = ft_strlen(*line);
	newline = (char*)malloc((len_line + len_buf + 1) * sizeof(char));
	if (!newline)
		return (0);
	while (*(*line + i))
	{
		newline[i] = *(*line + i);
		i++;
	}
	while (len_buf > 0)
	{
		newline[i++] = buf[j++];
		len_buf--;
	}
	newline[i] = '\0';
	free(*line);
	return (newline);
}

static int	ft_buf(char **line, char *buf)
{
	size_t i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
		{
			if (!(*line = ft_join(line, buf, i)))
				return (-1);
			buf = ft_remainder(buf, i + 1);
			return (1);
		}
		i++;
	}
	if (!(*line = ft_join(line, buf, i)))
		return (-1);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static char	*sbuf;
	ssize_t		sb;
	ssize_t		ret;

	if (fd < 0 || !(line))
		return (-1);
	ret = 0;
	if (!(*line = malloc(1)))
		return (-1);
	*line[0] = '\0';
	while (1)
	{
		if (sbuf)
			ret = ft_buf(line, sbuf);
		else if (!(sbuf = (char*)malloc((10 + 1) * sizeof(char))))
			return (-1);
		if (ret == 1 || ret == -1)
			return (ret);
		sb = read(fd, sbuf, 10);
		if (sb == 0)
			return (ft_free(&sbuf));
		if (sb == -1)
			return (-1);
		sbuf[sb] = '\0';
	}
}
