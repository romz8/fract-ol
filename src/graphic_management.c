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

t_frame  *init_graph(char **argv)
{
    t_image  *img;
    t_frame *frame;
    void    *mlx;
    void    *windw;

    frame = malloc(sizeof(t_frame));
    if (!frame)
        return (NULL);
    img = malloc(sizeof(t_image));
    if (!img)
        return (NULL);
    mlx = mlx_init();
    if (!mlx)
        return (NULL);
    windw = mlx_new_window(mlx, WIDTH, HEIGHT, "fractol");
    if (!windw)
        return (NULL);
    img->image = mlx_new_image(mlx, WIDTH, HEIGHT);
    if (!(img->image))
        return (NULL);
    img->addr = mlx_get_data_addr(img->image, &img->bits_per_pxl, &img->line_len, &img->endian);
    frame->mlx = mlx;
    frame->windw = windw;
    frame->img = img;
    if (argv[1])
        frame->color_setup = ft_atoi(argv[1]); // WARNING
    return (frame);
}

void   graphic_maganement(t_frame *vars)
{
    mlx_hook(vars->windw, 2, 0, esc_handler, vars);
    mlx_hook(vars->windw, 17, 0, close_handler, vars);
    mlx_mouse_hook(vars->windw, mouse_event, vars);
    mlx_key_hook(vars->windw, keyboard_events,vars);
    mlx_loop(vars->mlx);
}