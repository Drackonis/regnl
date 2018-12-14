/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkergast <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:39:03 by rkergast          #+#    #+#             */
/*   Updated: 2018/12/10 16:52:47 by rkergast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static int		check_error(int fd, char **line)
{
	if (fd < 0 || line == NULL || BUFF_SIZE < 1)
		return (-1);
	return (0);
}

static int		check_buffer(char buf[BUFF_SIZE], char **tab,\
		char **line, const int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strnew(BUFF_SIZE);
	printf ("WHILE BUF\n");
	while (buf[i])
	{
		printf ("BUF |%d| : |%c|\n", i, buf[i]);
		if (buf[i] == '\n')
		{
			if (tab[fd])
				tmp = tab[fd];
			tab[fd] = (ft_strcpy(ft_strnew(BUFF_SIZE - i), buf + i + 1));
			printf ("GET END BUF IN TAB : |%s|\n", tab[fd]);
			if (!*line)
				*line = ft_strncat(ft_strnew(i), buf, i);
			else
				*line = ft_strjoin(*line, ft_strncat(ft_strnew(i + 1), buf, i));
			printf ("COMPLETE LINE : |%s|\n", *line);
			if (tmp)
				free(tmp);
			return (1);
		}
		i++;
	}
	return (0);
}

static	int		get_buffer(char **tab, const int fd, char buf[BUFF_SIZE])
{
	int			ret;

	ret = 1;
	if (tab[fd] != NULL)
	{
		printf ("TAB FD EXIST : |%s|\n", tab[fd]);
		printf ("FD LEN : |%d|\n", ft_strlen(tab[fd]));
		if (ft_strlen(tab[fd]) == 0)
			return (-2);
		ft_strncpy(buf, tab[fd], BUFF_SIZE);
		free(tab[fd]);
		tab[fd] = NULL;
	}
	else
	{
		ret = read(fd, buf, BUFF_SIZE);
		buf[ret] = '\0';
		printf ("READ : |%s|\n", buf);
	}
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	static char		*tab[256];
	char			buf[BUFF_SIZE];
	int				ret;
	int				b;

	ret = 0;
	printf ("BEGIN\n");
	printf ("LINE : |%s|\n", *line);
	if (check_error(fd, line) == -1)
		return (-1);
	printf ("GET BUFFER\n");
	ret = get_buffer(tab, fd, buf);
	if (ret == 0 || ret == -2)
		return (0);
	printf ("CHECK BUFFER\n");
	b = check_buffer(buf, tab, line, fd);
	if (ret != 0 && b == 1)
		return (1);
	printf ("ADD BUFF : |%s|\n", buf);
	if (!*line)
		*line = ft_strsub(buf, 0, BUFF_SIZE);
	else
		*line = ft_strjoin(*line, buf);
	printf ("-----BOUCLE-----");
	//getchar();
	get_next_line(fd, line);
	if (ret > 1)
		ret = 1;
	return (ret);
}
