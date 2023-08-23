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
# define ZOOM 1.3

# define ESC 53
# define LEFT_CLICK 1
# define WHEEL_UP 5

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
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
    double cntr_re;
    double cntr_im;
    int     color_palette[100];
} t_fractal;

typedef struct s_frame
{
    void    *mlx;
    void    *windw;
    double x_click;
    double y_click;
    t_image  *img;
    t_fractal *set;
    char     color_setup;
}   t_frame;

t_frame  *init_graph(char **argv);
void   graphic_maganement(t_frame *vars);
int  esc_handler(int keycode, t_frame *vars);
int close_handler(t_frame *vars);
void    complex_cartesian_mapping(t_frame *frame);
int     mandelbrot_set(double c_re, double c_im);
void    mandelbrot_draw(t_frame *frame);

void    fill_pixel(t_image *data, int x, int y, int color);
int	create_trgb(int t, int r, int g, int b);
void    gradient_triple(t_fractal *f, int start, int mid, int end);
int     lerp_interpolation(int color1, int color2, float fraction);
void    color_range(t_frame *frame, t_fractal *f);
int     zoom_in(int key_code, t_frame *frame);
int     mouse_event(int key_code, int x, int y, t_frame *frame);

#endif
