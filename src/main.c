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
    t_frame  *frame;
    
    if (argc < 1 ||  !argv[0]) //useless but no compile with -W -W- W
        return (1);
    frame = init_graph();
    mandelbrot_draw(0, frame);
    graphic_maganement(frame);
}
