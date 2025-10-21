/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drw_aux.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 15:32:56 by ingonzal          #+#    #+#             */
/*   Updated: 2021/09/27 14:23:07 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "./mlx/mlx.h"

void	ft_init(t_cord *c)
{
	c->x = 650;
	c->y = 250;
	c->av = 0;
	c->ve = -1;
}

void	ft_plotlow(t_data *img, t_cord *c)
{
	c->dx = c->xb1 - c->xb;
	c->dy = c->yb1 - c->yb;
	c->yi = 1;
	if (c->dy < 0)
	{
		c->yi = -1;
		c->dy = c->dy * -1;
	}
	c->p = 2 * (c->dy - c->dx);
	while (c->xb++ < c->xb1)
	{
		if (c->xb < 1919 && c->yb < 1079 && c->xb > 0 && c->yb > 0)
			my_mlx_pixel_put(img, c->xb, c->yb, 0x00FFFFFF);
		if (c->p > 0)
		{
			c->yb = c->yb + c->yi;
			c->p = c->p + (2 * (c->dy - c->dx));
		}
		else
			c->p = c->p + (2 * c->dy);
	}
}

void	ft_plothigh(t_data *img, t_cord *c)
{
	c->dx = c->xb1 - c->xb;
	c->dy = c->yb1 - c->yb;
	c->xi = 1;
	if (c->dx < 0)
	{
		c->xi = -1;
		c->dx = c->dx * -1;
	}
	c->p = 2 * (c->dx - c->dy);
	while (c->yb++ < c->yb1)
	{
		if (c->xb < 1900 && c->yb < 1079 && c->xb > 0 && c->yb > 0)
			my_mlx_pixel_put(img, c->xb, c->yb, 0x00FFFFFF);
		if (c->p > 0)
		{
			c->xb = c->xb + c->xi;
			c->p = c->p + (2 * (c->dx - c->dy));
		}
		else
			c->p = c->p + (2 * c->dx);
	}
}

int	ft_close(int keycode, t_data *img)
{
	if (keycode == 53)
	{
		mlx_destroy_window(img->mlx, img->mlx_win);
		exit(1);
	}
	return (0);
}

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line + x * (data->bits / 8));
	*(unsigned int *) dst = color;
}
