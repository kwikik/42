/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3d_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddehili <ddehili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 16:54:03 by ddehili           #+#    #+#             */
/*   Updated: 2026/02/02 17:00:01 by ddehili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include <math.h>
#include <stdlib.h>

typedef struct s_point
{
	int	x;
	int	y;
	int	z;
}	t_point;

typedef struct s_fdf
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		**map;
	int		width;
	int		height;
	int		zoom;
	int		offset_x;
	int		offset_y;
}	t_fdf;

/* Dessiner un pixel dans l'image */
void	put_pixel(t_fdf *fdf, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < 1920 && y >= 0 && y < 1080)
	{
		dst = fdf->addr + (y * fdf->line_len + x * (fdf->bpp / 8));
		*(unsigned int *)dst = color;
	}
}

/* Projection isométrique : convertit (x,y,z) en coordonnées écran */
t_point	iso_project(int x, int y, int z, t_fdf *fdf)
{
	t_point	p;
	int		prev_x;
	int		prev_y;

	prev_x = x;
	prev_y = y;
	x = x * fdf->zoom;
	y = y * fdf->zoom;
	z = z * fdf->zoom;
	p.x = (prev_x - prev_y) * cos(0.523599) * fdf->zoom + fdf->offset_x;
	p.y = (prev_x + prev_y) * sin(0.523599) * fdf->zoom - z + fdf->offset_y;
	return (p);
}

/* Valeur absolue */
int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

/* Algorithme de Bresenham pour tracer une ligne */
void	draw_line(t_fdf *fdf, t_point p0, t_point p1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = ft_abs(p1.x - p0.x);
	dy = -ft_abs(p1.y - p0.y);
	sx = (p0.x < p1.x) ? 1 : -1;
	sy = (p0.y < p1.y) ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		put_pixel(fdf, p0.x, p0.y, color);
		if (p0.x == p1.x && p0.y == p1.y)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			p0.x += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			p0.y += sy;
		}
	}
}

/* Dessiner toute la carte : relier chaque point à ses voisins */
void	draw_map(t_fdf *fdf)
{
	int		x;
	int		y;
	t_point	current;
	t_point	next;

	y = 0;
	while (y < fdf->height)
	{
		x = 0;
		while (x < fdf->width)
		{
			current = iso_project(x, y, fdf->map[y][x], fdf);
			if (x < fdf->width - 1)
			{
				next = iso_project(x + 1, y, fdf->map[y][x + 1], fdf);
				draw_line(fdf, current, next, 0xFFFFFF);
			}
			if (y < fdf->height - 1)
			{
				next = iso_project(x, y + 1, fdf->map[y + 1][x], fdf);
				draw_line(fdf, current, next, 0xFFFFFF);
			}
			x++;
		}
		y++;
	}
}

/* Initialiser MiniLibX et afficher */
int	init_fdf(t_fdf *fdf)
{
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		return (0);
	fdf->win = mlx_new_window(fdf->mlx, 1920, 1080, "FdF");
	if (!fdf->win)
		return (0);
	fdf->img = mlx_new_image(fdf->mlx, 1920, 1080);
	fdf->addr = mlx_get_data_addr(fdf->img, &fdf->bpp,
			&fdf->line_len, &fdf->endian);
	fdf->zoom = 20;
	fdf->offset_x = 960;
	fdf->offset_y = 300;
	return (1);
}

/* Afficher l'image et lancer la boucle */
void	render(t_fdf *fdf)
{
	draw_map(fdf);
	mlx_put_image_to_window(fdf->mlx, fdf->win, fdf->img, 0, 0);
	mlx_loop(fdf->mlx);
}
