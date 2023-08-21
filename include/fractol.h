/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:18:23 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/21 14:18:25 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "../minilibx_opengl/mlx.h"

typedef struct s_data {
    void    *image;
    char    *addr;
    int     bits_per_pxl;
    int     line_len;
    int     endian;
}   t_data;

typedef struct s_vars
{
    void    *mlx;
    void    *windw;
    int     width;
    int     height;
    t_data  *data;
    t_mdbrt *m_set;
}   t_vars;

typedef struct s_mandelbrot_set
{
    int MaxReal;
    int MinReal;
    int MinIm;
    int MaxIm;
} t_mdbrt;

t_vars  *init_graph(char *s);
void   graphic_maganement(t_vars *vars);
int  esc_handler(int keycode, t_vars *vars);
int close_handler(t_vars *vars);

#endif
