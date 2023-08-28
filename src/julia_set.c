/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia_set.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/24 21:08:11 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/28 13:41:25 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int	julia_set(t_frame *f, double c_re, double c_im)
{
	int		n;
	double	z_re;
	double	z_im;
	double	temp;
	double	c[2];

	n = 0;
	z_re = c_re;
	z_im = c_im;
	julia_setup(f, c);
	while (n < MAX_ITER)
	{
		if (z_re * z_re + z_im * z_im > 4)
			return (n);
		temp = z_re * z_re - z_im * z_im + c[0];
		z_im = 2 * z_re * z_im + c[1];
		z_re = temp;
		n++;
	}
	return (-1);
}

void	julia_setup(t_frame *f, double c[2])
{
	if (f->julia_type == 1)
	{
		c[0] = -0.8;
		c[1] = 0.156;
	}
	else if (f->julia_type == 2)
	{
		c[0] = -0.7269;
		c[1] = 0.1889;
	}
	else if (f->julia_type == 3)
	{
		c[0] = -0.9;
		c[1] = 0.029;
	}
	else if (f->julia_type == 4)
	{
		c[0] = 1 - 1.618;
		c[1] = 0;
	}
	else
		fractol_exit(&f);
}
