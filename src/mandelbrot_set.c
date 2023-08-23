/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot_set.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 18:37:46 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/21 18:37:48 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../include/fractol.h"

void    complex_cartesian_mapping(t_frame *frame)
{       
    t_fractal *set = malloc(sizeof(t_fractal));
    if (!set)
        return ; //WARNING !!!!!!!! exit wrapping function here LATER ON
    set->MaxReal = 1;
    set->MinReal = -1.9;
    set->MinIm = -1.4;
    set->MaxIm = set->MinIm + (set->MaxReal - set->MinReal) * HEIGHT/ WIDTH;
    color_range(frame, set);
    frame->set = set;
}

int mandelbrot_set(double c_re, double c_im)
{
    int n;
    double  z_re;
    double  z_im;
    double  temp;

    n = 0;
    z_re = 0;
    z_im = 0;
    while ( n < MAX_ITER)
    {
        if (z_re * z_re + z_im * z_im > 4)
            return (n);
        temp = z_re;
        z_re = z_re * z_re  - z_im * z_im + c_re;
        z_im = 2 * temp * z_im + c_im; 
        n++;
    }
    return (0);
}

void    mandelbrot_draw(t_frame  *frame)
{
    double c_re;
    double c_im;
    int     y;
    int x;
    int     iteration;

    x = 0;
    while (x < WIDTH)
    {
        
        c_re = frame->set->MinReal + x * (frame->set->MaxReal - frame->set->MinReal) / WIDTH;
        y = 0;
        while (y < HEIGHT)
        {
            c_im = frame->set->MinIm + y * (frame->set->MaxIm - frame->set->MinIm)  / HEIGHT;
            iteration = mandelbrot_set(c_re, c_im);
            if (iteration == 0)
                fill_pixel(frame->img, x , y, 0x00000000);
            else
                fill_pixel(frame->img, x, y, frame->set->color_palette[iteration]);
            y++;
        }
        x++;
    }
    mlx_put_image_to_window(frame->mlx, frame->windw, frame->img->image, 0, 0);
}

void    fill_pixel(t_image *data, int x, int y, int color)
{
    char    *dst;

    if (!data)
        return ;
    dst = data->addr + (y * data->line_len + x * (data->bits_per_pxl / 8));
    *(unsigned int *) dst = color;
}
