/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:55:36 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/23 19:55:39 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

/*take as parameter: 
    1. the key_code from the hook function passed from mouse_event function
    2. Our frame object containing the window, the image, the fractal object
    and the mlx pointer
1. we re-scale our window ; we iniatilized it for the fractal set by framing 
our pxl grid to a complex plan where x-axis are reals and y- axix are Imaginary 
coordinate. we re-scale it for zooming by going into more details  (i.e : 
having the same nber of pixel on the axis but that represents smaller values :
we are going down in scale - ex : before 1080 pxl represented values from 
-1 to 1, now it's -0.5 to 0.5 : we increased details))
2. we need to direct that zoom : 
    2.a if the user clicked somewhere, we saved the corresponding complex 
    number coordinates to the fractal object, we keep that point of focus
    2.b. if the user never clicked (yet) - we assign the centre of the cmplex
    plane as the poit of focus
3. Now we zoom : we re-scale our screen around our point of fous :
the new min for x-axis is going toward our point of focus by half the
new window size / conversely for the y-axis with new imaginary axis values
4. We can now render again our fractal set, with new complex plan on same number 
of pixel (i.e same nber of details for same nber of complex points but on part
of complex plane that contains all the smaller values)
*/
int zoom_in(int key_code, t_frame *frame)
{
    t_fractal *f;
    double newWidth;
    double newHeight;

    if (key_code != WHEEL_UP)
        return (1);
    f = frame->set;  
    newWidth = (f->MaxReal - f->MinReal) / ZOOM;
    newHeight = (f->MaxIm - f->MinIm) / ZOOM;
    if (!f->cntr_re || !f->cntr_re)
    {
        f->cntr_re = (f->MaxReal + f->MinReal) / 2.0;
        f->cntr_im = (f->MaxIm + f->MinIm) / 2.0;
    }

    f->MinReal = f->cntr_re - newWidth / 2.0;
    f->MaxReal = f->cntr_re + newWidth / 2.0;
    f->MinIm = f->cntr_im - newHeight / 2.0;
    f->MaxIm = f->cntr_im + newHeight / 2.0;

    // PUT SOME INTERPOLATION TO SMOOTHEN THE ZOOM
    
    mandelbrot_draw(frame);
    return (0);
}

int  esc_handler(int keycode, t_frame *vars)
{
    if (keycode == ESC)
    {
        mlx_destroy_window(vars->mlx, vars->windw);
        exit (0);
    }
    else
        return (1);
}

int close_handler(t_frame *vars)
{
    mlx_destroy_window(vars->mlx, vars->windw);
    exit (0);
}

/* 
inputs are : key_code as per hooks function, coordinate of mouse, fractal object
1. If the user clicked -> convert the (x,y) pixel coordinate to a (re, im) complex 
plan and save it to our fractal object to direct "recursive" zoom
2. Apply the zoom_in function that will zoom in if the wheel is pressed up
*/
int mouse_event(int key_code, int x, int y, t_frame *frame)
{
    t_fractal *f;

    f = frame->set;
    if (key_code == LEFT_CLICK)
    {
        f->cntr_re = f->MinReal + (double) x * (f->MaxReal - f->MinReal) / WIDTH;
        f->cntr_im = f->MinIm + (double) y * (f->MaxIm - f->MinIm) / HEIGHT;
        return (0);
    }
    zoom_in(key_code, frame);
    return (1);
}

