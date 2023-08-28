/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/23 11:15:56 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/23 11:16:00 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"
/* 
Based on user input stored in the frame, we allocate a color gradient 
based on 3 colors with a function to the color_palette in the fractal object
 */
void    color_range(t_frame *frame)
{
    int i;

    i = 0;
    while ( i < MAX_ITER)
    {
        if (frame->color_setup == 1)
            frame->color_palette[i] = create_trgb(0, 50, 100 + i* 5, i * 5);
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
We create a triple color gradient based on the hex colors input start, mid, end
we use a 3 steps multi-strage : 
1. we will have a color palette of  MAX_ITER values (for instance 100)
2. we have 3 color segments : so we want 50 shades of colors betwwen start
and mid, then  50 shades of colors between mid and end
3. we interpolate between each colors as MAX_ITER / nb of segment 
*/
void    gradient_triple(t_frame *f, int start, int mid, int end)
{
    int i;
    int j;
    int color_start;
    int color_end;
    int key_colors[3];
    
    key_colors[0] = start;
    key_colors[1] = mid;
    key_colors[2] = end;
    i = 0;
    j = 0;
    while (j < 2)
    {
        color_start = key_colors[j];
        color_end = key_colors[j + 1];
        while (i < MAX_ITER / 3)
        {
            f->color_palette[j *  (MAX_ITER / 3) + i] = lerp_interpolation(color_start, color_end, (float) i / (MAX_ITER / 2));
            i++;
        }
        j++;
    }
}

/*
convert TRGB to HEX using bitshift as 0xTTRRGGBB = (T, R, G, B)
*/
int	create_trgb(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

/* 
creates a shade between 2 colors as an interpolation 
1. we take as input 2 colors (hex) and a fraction between [0, 1]
2. convert each color to TRGB - lfeft bitshift to mask it with 255 (full byte)
3. interpolate by returning the value in-between each R,G,B for  the 2 colors
    base on the fraction (it's like tracing a line and taking the point at distance
    equal to fraction)
4. return the hex color corresponding 
*/
int lerp_interpolation(int color1, int color2, float fraction)
{
    int trgb_start[4];
    int trgb_end[4];
    int trgb_inter[4];
    int i;
    
    trgb_start[0] = (color1 >> 24) & 0xFF;
    trgb_start[1] = (color1 >> 16) & 0xFF;
    trgb_start[2] = (color1 >> 8) & 0xFF;
    trgb_start[3] = (color1) & 0xFF;
    trgb_end[0] = (color2 >> 24) & 0xFF;
    trgb_end[1] = (color2 >> 16) & 0xFF;
    trgb_end[2] = (color2 >> 8) & 0xFF;
    trgb_end[3] = (color2) & 0xFF;
    i = -1;
    while (++i < 4)
    {
        trgb_inter[i] = trgb_start[i] + fraction * (trgb_end[i] - trgb_start[i]);
        if (trgb_inter[i] > 255) 
            trgb_inter[i] = 255;
        if (trgb_inter[i] < 0)
            trgb_inter[i] = 0;
    }
    return (create_trgb(trgb_inter[0], trgb_inter[1], trgb_inter[2], trgb_inter[3]));
}