/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 20:59:39 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/28 14:07:25 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	fractal_set(t_frame *frame, double c_re, double c_im)
{
	if (frame->type == 1)
		return (mandelbrot_set(c_re, c_im));
	else if (frame->type == 2)
		return (julia_set(frame, c_re, c_im));
	else
		return (burningship_set(c_re, c_im));
}

void	render_fractal(t_frame *frame, int iteration)
{
	double	c_re;
	double	c_im;
	int		y;
	int		x;

	x = 0;
	while (x < WIDTH)
	{
		c_re = frame->min_re + x * (frame->max_re - frame->min_re) / WIDTH;
		y = 0;
		while (y < HEIGHT)
		{
			c_im = frame->min_im + y * (frame->max_im - frame->min_im) 
				/ HEIGHT;
			iteration = fractal_set(frame, c_re, c_im);
			if (iteration == -1)
				fill_pixel(frame, x, y, 0x00000000);
			else
				fill_pixel(frame, x, y, frame->color_palette[iteration]);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(frame->mlx, frame->windw, frame->image, 0, 0);
}

void	fill_pixel(t_frame *frame, int x, int y, int color)
{
	char	*dst;

	if (!frame)
		return ;
	dst = frame->addr + (y * frame->line_len + x * (frame->bits_per_pxl / 8));
	*(unsigned int *) dst = color;
}

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
int	zoom(int key_code, double x, double y, t_frame *f)
{
	double	axis_width;
	double	axis_height;
	double	zoom;

	if (key_code == WHEEL_UP)
		zoom = ZOOM;
	else if (key_code == WHEEL_DOWN)
		zoom = 1 / ZOOM;
	else
		return (1); 
	axis_width = (f->max_re - f->min_re);
	axis_height = (f->max_im - f->min_im);
	f->cntr_re = f->min_re + (double) x * axis_width / WIDTH;
	f->cntr_im = f->min_im + (double) y * axis_height / HEIGHT;
	f->min_re = f->cntr_re - (fabs(f->min_re - f->cntr_re) / zoom);
	f->min_im = f->cntr_im - (fabs(f->min_im - f->cntr_im) / zoom);
	f->max_im = f->cntr_im + (fabs(f->max_im - f->cntr_im) / zoom);
	f->max_re = f->cntr_re + (fabs(f->max_re - f->cntr_re) / zoom);
	render_fractal(f, 0);
	return (0);
}
