/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ingonzal <ingonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/04 19:44:13 by ingonzal          #+#    #+#             */
/*   Updated: 2021/09/26 14:41:35 by ingonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#ifndef FDF_H
# define FDF_H
# include <stdlib.h>

typedef struct s_data{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits;
	int			line;
	int			end;
	uintptr_t	col;
}	t_data;

typedef struct s_cord{
	int	x;
	int	x1;
	int	y;
	int	y1;
	int	av;
	int	ve;
	int	z;
	int	z1;
	int	dx;
	int	dy;
	int	p;
	int	xi;
	int	yi;
	int	xb;
	int	xb1;
	int	yb;
	int	yb1;
}	t_cord;

typedef struct s_a{
	int			x;
	int			y;
	int			fd;
	char		*tab;
	int			**m;
}	t_a;

void	ft_draw(t_a *a);
void	ft_brasenham(t_data *img, t_cord *c);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		ft_close(int keycode, t_data *img);
void	ft_plotlow(t_data *img, t_cord *c);
void	ft_plothigh(t_data *img, t_cord *c);
void	ft_reverse(t_cord *c);
void	ft_init(t_cord *c);
void	ft_draw_x(t_a *a, t_data *img, t_cord *c);
void	ft_draw_y(t_a *a, t_data *img, t_cord *c);

#endif
