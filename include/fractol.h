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
# define MAX_ITER 80
# define ZOOM 1.3

# define ESC 53
# define LEFT_CLICK 1
# define WHEEL_UP 5
# define WHEEL_DOWN 4
# define ARROW_UP 126
# define ARROW_DOWN 125
# define ARROW_LEFT 123
# define ARROW_RIGHT 124

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include "../minilibx_opengl/mlx.h"
# include "../libft/libft.h"

typedef struct s_fractal
{  

} t_fractal;

typedef struct s_frame
{
    void    *mlx;
    void    *windw;
    void    *image;
    char    *addr;
    int     bits_per_pxl;
    int     line_len;
    int     endian;
    int     color_setup;
    int     type;
    double MaxReal;
    double MinReal;
    double MinIm;
    double MaxIm;
    double cntr_re;
    double cntr_im;
    int     julia_type;
    int     color_palette[80];
}   t_frame;

void    init_graph(char **argv, t_frame *frame);
void    args_exit(void);
int     esc_handler(int keycode, t_frame *vars);
int     close_handler(t_frame *vars);
void    complex_plan(t_frame *frame);
int     mandelbrot_set(double c_re, double c_im);
void    render_fractal(t_frame  *frame, int iteration);
void    fill_pixel(t_frame *frame, int x, int y, int color);
int     create_trgb(int t, int r, int g, int b);
void    gradient_triple(t_frame *f, int start, int mid, int end);
int     lerp_interpolation(int color1, int color2, float fraction);
void    color_range(t_frame *frame);
int     zoom(int key_code, double x, double y, t_frame *frame);
int     mouse_event(int key_code, int x, int y, t_frame *frame);
int     keyboard_events(int keycode, t_frame *frame);
void    move(t_frame *frame, double x, double y);
void    fractol_exit(t_frame **frame);
void    fractal_setup(t_frame *frame, char **argv);
int     julia_set( t_frame *f, double c_re, double c_im);
void    julia_setup(t_frame *f, double c[2]);
int     burningship_set(double c_re, double c_im);

#endif
