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

void    complex_plan(t_frame *frame)
{       
    t_fractal *set;

    set = frame->set;
    if (frame->set->type == 2)
    {
    set->MaxReal = 1.5;
    set->MinReal = -1.5;
    set->MinIm = -1.5;   
    }
    else
    {
        set->MaxReal = 1;
        set->MinReal = -1.9;
        set->MinIm = -1.4;
    }
    set->MaxIm = set->MinIm + (set->MaxReal - set->MinReal) * HEIGHT/ WIDTH;
    color_range(frame, set);
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
    return (-1);
}