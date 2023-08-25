/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rjobert <rjobert@student.42barcelo>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:27:28 by rjobert           #+#    #+#             */
/*   Updated: 2023/08/21 17:27:31 by rjobert          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fractol.h"

void    init_graph(char **argv, t_frame *frame)
{
   
    frame->mlx = mlx_init();
    if (!frame->mlx)
        return ;
    frame->windw = mlx_new_window(frame->mlx, WIDTH, HEIGHT, "fractol");
    if (!frame->windw)
        return ;
    frame->image = mlx_new_image(frame->mlx, WIDTH, HEIGHT);
    if (!(frame->image))
        return ;
    frame->addr = mlx_get_data_addr(frame->image, &frame->bits_per_pxl, &frame->line_len, &frame->endian);
    if (argv[2])
        frame->color_setup = ft_atoi(argv[2]); // WARNING
    fractal_setup(frame, argv);
    return ;
}

void    args_exit(void)
{
    ft_putstr_fd("\nWRONG ARGUMENTS :\n",STDOUT_FILENO);
    ft_putstr_fd("Please enter the parameeters as follow:\n", STDOUT_FILENO);
    ft_putstr_fd("\n==============================================\n\n", STDOUT_FILENO);
    ft_putstr_fd("./fractol \nTHEN ENTER:\n", STDOUT_FILENO);
    ft_putstr_fd("\targument 1 : 'Mandelbrot','Julia' or 'BurningShip' \n", STDOUT_FILENO);
    ft_putstr_fd("\targument 2 : [1 to 4] for colors setup\n", STDOUT_FILENO);
    ft_putstr_fd("\targument 3 (IF JULIA SET): [1 to 4] for set type\n", STDOUT_FILENO);
    ft_putstr_fd("\n==============================================\n\n", STDOUT_FILENO);
    ft_putstr_fd("EXAMPLE\n", STDOUT_FILENO);
    ft_putstr_fd("\t./fractol Mandelbrot 4\n\n", STDOUT_FILENO);
}