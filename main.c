/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkergast <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 16:58:25 by rkergast          #+#    #+#             */
/*   Updated: 2018/12/14 15:33:21 by rkergast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		main(void)
{
	int		fd;
	char	**line;
	int		tmp;
	int		i;

	i = 0;
	i = 0;
	tmp = 1;
	if ((fd = open("test42", O_RDWR | O_CREAT | O_APPEND, S_IRWXU)) == -1)
		return (1);
	if (!(line = (char**)malloc(sizeof(char*) * BUFF_SIZE)))
		return (1);
	*line = NULL;
	while (tmp == 1)
	{
		tmp = get_next_line(fd, line);
		printf("%s\n", *line);
		i++;
		free(*line);
		*line = NULL;
	}
	if (close(fd) == -1)
		return (1);
	return (0);
}
