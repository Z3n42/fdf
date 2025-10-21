/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 13:26:55 by ingonzal          #+#    #+#             */
/*   Updated: 2021/09/26 14:35:37 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./mlx/mlx.h"
#include <math.h>

void	ft_reverse(t_cord *c)
{
	int	swap;

	swap = c->xb;
	c->xb = c->xb1;
	c->xb1 = c->yb1;
	c->yb1 = c->yb;
	c->yb = c->xb1;
	c->xb1 = swap;
}

void	ft_brasenham(t_data *img, t_cord *c)
{
	if (abs(c->yb1 - c->yb) < abs(c->xb1 - c->xb))
	{
		if (c->xb > c->xb1)
		{
			ft_reverse(c);
			ft_plotlow(img, c);
		}
		else
			ft_plotlow(img, c);
	}
	else
	{
		if (c->yb > c->yb1)
		{
			ft_reverse(c);
			ft_plothigh(img, c);
		}
		else
			ft_plothigh(img, c);
	}
}

void	ft_draw_x(t_a *a, t_data *img, t_cord *c)
{
	ft_init(c);
	c->x1 = c->x + 800 / a->x;
	c->y1 = c->y;
	while (++c->ve < a->y)
	{
		while (c->av < a->x - 1)
		{
			c->xb = (((c->x - c->y) * cos(0.7)) + 600);
			c->yb = ((c->y + c->x) * sin(0.7)) - 450 - a->m[c->ve][c->av] * 5;
			c->xb1 = (((c->x1 - c->y1) * cos(0.7)) + 600);
			c->yb1 = (c->y1 + c->x1) * sin(0.7) - 450
				- a->m[c->ve][c->av + 1] * 5;
			ft_brasenham(img, c);
			c->x = c->x1;
			c->x1 += 800 / a->x;
			c->av++;
		}
		c->x = 650;
		c->x1 = c->x + 800 / a->x;
		c->av = 0;
		c->y += 500 / a->y;
		c->y1 += 500 / a->y;
	}		
}

void	ft_draw_y(t_a *a, t_data *img, t_cord *c)
{
	ft_init(c);
	c->x1 = c->x;
	c->y1 = c->y + 500 / a->y;
	while (++c->ve < a->x)
	{
		while (c->av < a->y - 1)
		{
			c->xb = (c->x - c->y) * cos(0.7) + 600;
			c->yb = ((c->y + c->x) * sin(0.7)) - 450 - (a->m[c->av][c->ve]) * 5;
			c->xb1 = ((c->x1 - c->y1) * cos(0.7)) + 600;
			c->yb1 = ((c->y1 + c->x1) * sin(0.7)) - 450
				- a->m[c->av + 1][c->ve] * 5;
			ft_brasenham(img, c);
			c->y = c->y1;
			c->y1 += 500 / a->y;
			c->av++;
		}
		c->y = 250;
		c->y1 = c->y + 500 / a->y;
		c->av = 0;
		c->x += 800 / a->x;
		c->x1 += 800 / a->x;
	}
}

void	ft_draw(t_a *a)
{
	t_data	img;
	t_cord	c;

	img.mlx = mlx_init();
	img.mlx_win = mlx_new_window(img.mlx, 1920, 1080, "FDF");
	img.img = mlx_new_image(img.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits, &img.line, &img.end);
	ft_draw_x(a, &img, &c);
	ft_draw_y(a, &img, &c);
	mlx_put_image_to_window(img.mlx, img.mlx_win, img.img, 0, 0);
	mlx_key_hook(img.mlx_win, ft_close, &img);
	mlx_loop(img.mlx);
}
