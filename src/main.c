/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 14:16:41 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/21 14:16:48 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

int main(int argc, char *argv[])
{
    t_vars  *frame;
    void    *set;
    int     img_width;
    int     img_height;
    
    if (argc < 2)
        return (1);
    frame = init_graph(argv[1]);
    set = mlx_xpm_file_to_image(frame->mlx, "./img/mandelbrot_set.xpm", &img_width, &img_height);
    if (!set)
        return(1);
    mlx_put_image_to_window(frame->mlx, frame->windw, set, 0, 0);
    graphic_maganement(frame);
}

