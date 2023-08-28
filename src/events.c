/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 19:55:36 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/28 13:29:45 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	esc_handler(int keycode, t_frame *vars)
{
	if (keycode == ESC)
	{
		mlx_destroy_window(vars->mlx, vars->windw);
		exit (0);
	}
	else
		return (1);
}

int	close_handler(t_frame *vars)
{
	mlx_destroy_window(vars->mlx, vars->windw);
	exit (0);
}

/* 
inputs are : key_code as per hooks function, coordinate of mouse, fractal object
1. If the user clicked -> convert the (x,y) pixel coordinate to a (re, im) 
complex plan and save it to our fractal object to direct "recursive" zoom
2. Apply the zoom_in function that will zoom in if the wheel is pressed up
*/
int	mouse_event(int key_code, int x, int y, t_frame *frame)
{
	if (key_code == RIGHT_CLICK)
	{
		frame->color_setup += 1;
		frame->color_setup %= 5;
		color_range(frame);
		render_fractal(frame, 0);
	}
	zoom(key_code, (double) x, (double)y, frame);
	return (1);
}

int	keyboard_events(int keycode, t_frame *frame)
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

void	move(t_frame *f, double x, double y)
{
	double	distance_re;
	double	distance_im;

	if (!f)
		return ;
	distance_re = (f->max_re - f->min_re);
	distance_im = (f->max_im - f->min_im);
	f->max_re += distance_re * x * 0.03;
	f->min_re += distance_re * x * 0.03;
	f->max_im += distance_im * y * 0.03;
	f->min_im += distance_im * y * 0.03;
	render_fractal(f, 0);
}
