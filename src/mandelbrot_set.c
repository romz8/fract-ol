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
    if (!frame)
        return ;
    if (frame->type == 2)
    {
        frame->MaxReal = 1.5;
        frame->MinReal = -1.5;
        frame->MinIm = -1.5;   
    }
    else
    {
        frame->MaxReal = 1;
        frame->MinReal = -1.9;
        frame->MinIm = -1.4;
    }
    frame->MaxIm = frame->MinIm + (frame->MaxReal - frame->MinReal) * HEIGHT/ WIDTH;
    color_range(frame);
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

int burningship_set(double c_re, double c_im)
{
    int n;
    double  z_re;
    double  z_im;
    double  temp;

    n = 0;
    z_re = c_re;
    z_im = c_im;
    while ( n < MAX_ITER)
    {
        z_re = fabs(z_re);
        z_im = fabs(z_im);
        if (z_re * z_re + z_im * z_im > 4)
            return (n);
        temp = z_re;
        z_re = z_re * z_re  - z_im * z_im + c_re;
        z_im = 2 * temp * z_im + c_im; 
        n++;
    }
    return (-1);
}