/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 19:16:24 by ingonzal          #+#    #+#             */
/*   Updated: 2021/09/05 14:27:39 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <unistd.h>
#include <stdlib.h>

int	get_next_line(int fd, char **line)
{	
	char			*buf;
	ssize_t			res;
	static char		*array;
	int				end;
	int				lel;

	if (fd < 0 || fd > 999 || line == NULL)
		return (-1);
	res = 1;
	buf = (char *)malloc(sizeof (char) + 1);
	while (res > 0 && ft_strchr_gnl(array, '\n') == NULL)
	{
		res = read(fd, buf, 1);
		buf[res] = '\0';
		array = ft_strjoin_gnl(array, buf);
	}
	free(buf);
	end = ft_strlen_gnl(array, '\n');
	*line = ft_substr_gnl(array, 0, end);
	lel = ft_strlen_gnl(*line, 0);
	if (res != -1)
		array = ft_substr2_gnl(array, (end + 1), (ft_strlen_gnl(array, 0) - lel));
		if (res > 1)
		res = 1;
	return (res);
}
