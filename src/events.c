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

/*
Take as parameter: 
    1. the key_code from the hook function passed from mouse_event function
    2. the mouse position on the grid (in pixel)
    3. Our frame object containing the window, the image, the fractal object
    and the mlx pointer
1. we calculate the length of our axis on our complex plan by taking the 
(max - min) difference for both real and imaginary part -> the idea is to reduce 
this axis value range (in our complex plan) for the same nber of pxl on our 
screen: i.e. : zooming = more details = having the same nber of pixel on the 
axis but that represents smaller values
2. we re-scale our mouse position (x, y) from pixel grid to our complex grid : 
we factor our x (pixel width) to our real_axis by starting at the min_real and 
then add the distance x * axis_size / WIDTH ; this like applying a ratio of
conversion from pixel to complex plan. we do the same for y and imaginary axis. 
that gives us a focal point in the complex plan from our mouse position.
3. we re-scale our window ; we iniatilized it for the fractal set by framing 
our pxl grid to a complex plan where x-axis are reals and y-axis are Imaginary 
coordinate. We now re-scale it around our focal point: 

Example with real_axis(x) : 
we calculate the distance between the previous min and the focal point and 
divide it by the zoom (to have a smaller axis on the same nbr of pixels) - 
similarly we calculate the distance betwn the pvious max and our focal point. 
our new min and max for reals (x) will be our focal point - / + this distance. 
we do the same for the imaginary (y) axis with minIm and maxIm.

4. We re-render our fractal but this time on smaller complex planm, centered 
around our focal point - but for the same nber of pxl on our screen.
*/

int zoom(int key_code, double x, double y, t_frame *frame)
{
    t_fractal *f;
    double axis_Width;
    double axis_Height;
    double  zoom;


    if (key_code == WHEEL_UP)
        zoom = ZOOM;
    else if (key_code == WHEEL_DOWN)
        zoom = 1 / ZOOM;
    else
        return (1);
    f = frame->set;  
    axis_Width = (f->MaxReal - f->MinReal);
    axis_Height = (f->MaxIm - f->MinIm);
    f->cntr_re = f->MinReal + (double) x * axis_Width / WIDTH;
    f->cntr_im = f->MinIm + (double) y * axis_Height / HEIGHT;
	f->MinReal = f->cntr_re - (fabs(f->MinReal - f->cntr_re) / zoom);
	f->MinIm = f->cntr_im - (fabs(f->MinIm- f->cntr_im) / zoom);
	f->MaxIm = f->cntr_im + (fabs(f->MaxIm - f->cntr_im) / zoom);
	f->MaxReal = f->cntr_re + (fabs(f->MaxReal - f->cntr_re) / zoom);
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
    if (key_code == LEFT_CLICK)
    {
        
        frame->color_setup += 1;
        frame->color_setup %= 4;
        color_range(frame, frame->set);
        mandelbrot_draw(frame);
    }
    zoom(key_code, (double) x, (double)y, frame);
    return (1);
}

int keyboard_events(int keycode, t_frame *frame)
{
    if (keycode == ARROW_UP)
        move(frame, 0, -1);
    else if (keycode == ARROW_DOWN)
        move(frame, 0, +1);
    else if (keycode == ARROW_LEFT)
        move(frame, -1, 0);
    else if (keycode == ARROW_RIGHT)
        move (frame, +1, 0);
    return (0);   
}

void    move(t_frame *frame, double x, double y)
{
    t_fractal *f;
    double  distance_Re;
    double  distance_Im;

    if (!frame)
        return;
    f = frame->set;
    distance_Re = (f->MaxReal - f->MinReal);
    distance_Im =  (f->MaxIm - f->MinIm);
    f->MaxReal += distance_Re * x * 0.03;
    f->MinReal += distance_Re * x * 0.03;
    f->MaxIm += distance_Im * y * 0.03;
    f->MinIm += distance_Im * y * 0.03;
    mandelbrot_draw(frame);
}