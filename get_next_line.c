/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: woliveir <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 20:13:12 by woliveir          #+#    #+#             */
/*   Updated: 2017/02/15 16:34:53 by woliveir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./libft/libft.h"
#include "./get_next_line.h"

int				get_next_line(const int fd, char **line)
{
	int			got;
	char		*p;
	static char	*n = NULL;

	if ((!n && (n = ft_memalloc(sizeof(char))) == NULL) || line == NULL)
		return (-1);
	p = ft_strchr(n, '\n');
	while (p == NULL)
	{
		if ((got = ft_io(fd, &n)) == 0)
			if ((p = ft_strchr(n, '\0')) == n)
				return (0);
		if (got < 0)
			return (-1);
		else if (got != 0)
			p = ft_strchr(n, '\n');
	}
	*line = ft_strsub(n, 0, (p - n));
	p = ft_strdup(p + 1);
	free(n);
	n = p;
	return (1);
}

int				ft_io(int const fd, char **n)
{
	int			got;
	char		buffer[BUFF_SIZE + 1];
	char		*ar;

	ft_memset(buffer, '\0', (BUFF_SIZE + 1));
	got = read(fd, buffer, BUFF_SIZE);
	if (got > 0)
	{
		buffer[got] = '\0';
		ar = ft_strjoin(*n, buffer);
		if (!ar)
			return (-1);
		free(*n);
		*n = ar;
	}
	return (got);
}
