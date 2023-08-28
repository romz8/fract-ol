/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:15:56 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/28 13:24:12 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"
/* 
Based on user input stored in the frame, we allocate a color gradient 
based on 3 colors with a function to the color_palette in the fractal object
 */
void	color_range(t_frame *frame)
{
	int	i;

	i = 0;
	while (i < MAX_ITER)
	{
		if (frame->color_setup == 1)
			frame->color_palette[i] = create_trgb(0, 50, 100 + i * 5, i * 5);
		else if (frame->color_setup == 2)
			frame->color_palette[i] = create_trgb(0, i * 5, 20, 20 + i * 5);
		else if (frame->color_setup == 3)
			frame->color_palette[i] = create_trgb(0, 150 + i * 5, 0, i * 15);
		else
		{
			frame->color_palette[i] = create_trgb(0, 50 + i * 5, i * 5, 20);
			frame->color_setup = 0;
		}
		i++;
	}
}

/*
convert TRGB to HEX using bitshift as 0xTTRRGGBB = (T, R, G, B)
*/
int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}
