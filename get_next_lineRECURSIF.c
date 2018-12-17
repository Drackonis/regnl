/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkergast <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:39:03 by rkergast          #+#    #+#             */
/*   Updated: 2018/12/17 17:02:32 by rkergast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char		**check_error(int fd, char **line)
{
	if (!(line = (char**)malloc(sizeof(char*) * BUFF_SIZE)))
		return (NULL);
	if (fd < 0 || line == NULL || BUFF_SIZE < 1)
		return (NULL);
	*line = NULL;
	return (line);
}

static int		check_buffer(char buf[BUFF_SIZE], char **tab,\
		char **line, const int fd)
{
	int		i;
	char	*tmp;

	i = 0;
	tmp = ft_strnew(BUFF_SIZE);
	while (buf[i])
	{
		printf ("-BUF %d : |%c|\n", i, buf[i]);
		printf ("-BUF : |%s|\n", buf);
		if (buf[i] == '\n')
		{
			printf ("-BACKSLASH N\n");
			if (tab[fd])
				tmp = tab[fd];
			tab[fd] = (ft_strcpy(ft_strnew(BUFF_SIZE - i), buf + i + 1));
			printf ("-ADD BUF IN TAB : |%s|\n", tab[fd]);
			if (!*line)
				*line = ft_strncat(ft_strnew(i + 1), buf, i);
			else
				*line = ft_strjoin(*line, ft_strncat(ft_strnew(i + 1), buf, i));
			printf ("-CREATE AND ADD IN LINE : |%s|\n", *line);
			ft_bzero(tab[fd], i);
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
	if (tab[fd] != NULL && ft_strlen(tab[fd]) > 0)
	{
		printf ("TAB EXIST : |%s|\n", tab[fd]);
		ft_strncpy(buf, tab[fd], BUFF_SIZE);
		free(tab[fd]);
		tab[fd] = NULL;
	}
	else
	{
		ret = read(fd, buf, BUFF_SIZE);
		buf[ret] = '\0';
		printf ("-READ : |%s|\n", buf);
	}
	return (ret);
}

int				get_next_line(const int fd, char **line)
{
	static char		*tab[256];
	char			buf[BUFF_SIZE];
	int				ret;
	int				b;

	printf ("************\nBEGIN\n************\n");
	printf ("-CURRENT LINE : |%s|\n", *line);
	ret = 0;
	if (*line == NULL)
		if ((line = check_error(fd, line)) == NULL)
			return (-1);
	printf("LINE = |%s|\n", *line);
	ret = get_buffer(tab, fd, buf);
	printf ("-GET BUFFER RET : %d\n", ret);
	/*if (ret == 0)
		return (0);*/
	b = check_buffer(buf, tab, line, fd);
	printf ("-DONT FIND /n\n");
	printf ("-BUF : |%s|\n", buf);
	if (b == 0)
	{
		if (!*line)
		{
			printf ("-PASS HERE\n");
			*line = ft_strdup(buf);
		}
		else
		{
			printf ("-OR HERE\n");
			*line = ft_strjoin(*line, buf);
		}
	}
	//printf ("-COPY BUF IN LINE\n");
	printf ("-NEW LINE : |%s|\n", *line);
	if (b == 1)
		return (1);
	printf ("-BOUCLE\n_____________\n");
	get_next_line(fd, line);
	if (ret > 1)
		ret = 1;
	return (ret);
}
