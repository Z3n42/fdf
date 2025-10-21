/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 13:17:59 by ingonzal          #+#    #+#             */
/*   Updated: 2021/09/28 13:21:25 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include "./libft/libft.h"

int	ft_xcount(char const *s, char c)
{
	int	counter;
	int	pos;

	if (!s)
	{
		write(1, "Map Error\n", 10);
		exit(1);
	}
	counter = 0;
	pos = 0;
	while (s[counter])
	{
		if (s[counter] == c && s[counter + 1] != c)
			pos++;
		counter++;
	}
	if (s[counter - 1] == ' ')
		return (pos);
	else
		return (pos + 1);
}

int	**ft_matrix(int fd, int x, int y)
{
	char	**tbl;
	char	*str;
	int		**mat;
	int		i;
	int		j;

	mat = (int **)malloc(y * sizeof(int *));
	j = 0;
	while (get_next_line(fd, &str))
	{
		tbl = ft_split(str, ' ');
		free(str);
		i = 0;
		mat[j] = (int *)malloc(x * sizeof(int));
		while (tbl[i])
		{
			mat[j][i] = ft_atoi(tbl[i]);
			free(tbl[i]);
			i++;
		}
		free(tbl);
		j++;
	}
	free(str);
	return (mat);
}

void	ft_open(t_a *a, char *argv)
{
	if (!argv)
	{
		write(1, "Map Error\n", 10);
		exit(1);
	}
	a->fd = open(argv, O_RDONLY);
	get_next_line(a->fd, &a->tab);
	a->x = ft_xcount(a->tab, ' ');
	free(a->tab);
	a->y = 1;
	while (get_next_line(a->fd, &a->tab))
	{
		free(a->tab);
		a->y++;
	}
	free(a->tab);
	if (a->x < 2 || a->y < 2)
	{
		write(1, "Map Error\n", 10);
		exit(1);
	}
	close(a->fd);
}

int	main(int argc, char **argv)
{
	t_a	a;
	int	i;

	if (argc != 2)
	{
		write(1, "Map Error\n", 10);
		exit(1);
	}
	ft_open(&a, argv[1]);
	a.fd = open(argv[1], O_RDONLY);
	a.m = ft_matrix(a.fd, a.x, a.y);
	ft_draw(&a);
	i = 0;
	while (i < a.y)
	{
		free(a.m[i]);
		i++;
	}
	free(a.m);
}
