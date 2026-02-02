/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddehili <ddehili@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 14:51:57 by ddehili           #+#    #+#             */
/*   Updated: 2026/02/02 17:01:05 by ddehili          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#	ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
#include <stdio.h>  
#include <stdlib.h>
#include "get_next_line.h"
#include "mlx.h"
#include <math.h>


typedef struct s_tabdim
{
	int	x;
	int	y;
}	t_tabdim;

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

/* Prototypes des fonctions de 3d_utils.c */
void	put_pixel(t_fdf *fdf, int x, int y, int color);
t_point	iso_project(int x, int y, int z, t_fdf *fdf);
void	draw_line(t_fdf *fdf, t_point p0, t_point p1, int color);
void	draw_map(t_fdf *fdf);
int		init_fdf(t_fdf *fdf);
void	render(t_fdf *fdf);

char	*get_next_line(int fd);
char	*ft_strdup(const char *s);
char	*strjoin(char *rest, char *buffer);
void	ft_strcpy(char *dst, char *src);
int		ft_strlen(char *s);

#endif