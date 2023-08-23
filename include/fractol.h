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

# ifndef WIDTH
#  define WIDTH 1080
# endif
# ifndef HEIGHT
#  define HEIGHT 1080
# endif
# define MAX_ITER 100

# define ESC 53

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include "../minilibx_opengl/mlx.h"

typedef struct s_image {
    void    *image;
    char    *addr;
    int     bits_per_pxl;
    int     line_len;
    int     endian;
}   t_image;

typedef struct s_fractal
{
    double MaxReal;
    double MinReal;
    double MinIm;
    double MaxIm;
    double Re_factor;
    double Im_factor;
    int     color_palette[100];
} t_fractal;

typedef struct s_vars
{
    void    *mlx;
    void    *windw;
    t_image  *img;
    t_fractal *m_set;
    char     color_setup;
}   t_frame;

t_frame  *init_graph(char **argv);
void   graphic_maganement(t_frame *vars);
int  esc_handler(int keycode, t_frame *vars);
int close_handler(t_frame *vars);
void    complex_cartesian_mapping(t_frame *frame);
int     mandelbrot_set(double c_re, double c_im);
void    mandelbrot_draw(int x, t_frame *frame);

void    fill_pixel(t_image *data, int x, int y, int color);
int	create_trgb(int t, int r, int g, int b);
void    gradient_triple(t_fractal *f, int start, int mid, int end);
int     lerp_interpolation(int color1, int color2, float fraction);
void    color_range(t_frame *frame, t_fractal *f);



#endif
