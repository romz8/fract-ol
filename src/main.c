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
void    fractal_setup(t_frame *frame, char **argv)
{

    if (ft_strncmp(argv[1], "Mandelbrot",10) == 0)
        frame->type = 1;
    else if (ft_strncmp(argv[1], "Julia",5) == 0)
        frame->type = 2;
    else if (ft_strncmp(argv[1], "BurningShip",11) == 0)
        frame->type = 3;
    else
        fractol_exit(&frame);
    if (frame->type == 2)
    {   
        if (!argv[3] || !argv[2])
            fractol_exit(&frame);
        else if (argv[3] && (ft_strncmp(argv[3], "1", 1) || 
        ft_strncmp(argv[3], "2", 1) || ft_strncmp(argv[3], "3", 1)))
            frame->julia_type = ft_atoi(argv[3]);
        else
            fractol_exit(&frame);
    }
    return ;
}

void fractol_exit(t_frame **frame)
{
    args_exit();
    if (!*frame)
        return ;
    if ((*frame)->frame_init != 1)
        exit (0);
    if ((*frame)->image && (*frame)->frame_init == 1)
        mlx_destroy_image((*frame)->mlx, (*frame)->image);
    if ((*frame)->windw && (*frame)->frame_init == 1)
        mlx_destroy_window((*frame)->mlx, (*frame)->windw);
    exit(0);
}

void fractol_commandes(void)
{
    ft_putstr_fd("\nHERE ARE THE COMMANDS :\n",STDOUT_FILENO);
    ft_putstr_fd("\n==============================================\n\n", STDOUT_FILENO);
    ft_putstr_fd("\nMOUSE WHEEL : zoon in / out\n", STDOUT_FILENO);
    ft_putstr_fd("\nRIGHT CLICK : Change colors of the set \n", STDOUT_FILENO);
    ft_putstr_fd("\nARROW (<-, ->, up, down): moove in the plan\n", STDOUT_FILENO);
    ft_putstr_fd("\n\n==============================================\n\n", STDOUT_FILENO); 
}

int main(int argc, char *argv[])
{
    t_frame  frame;
    
    if (argc < 2 || !argv[1] || argv[1][0] == '\0')
    {
        args_exit();
        return (1);
    }
    frame.frame_init = 0;
    fractal_setup(&frame, argv);
    init_graph(argv, &frame);
    complex_plan(&frame);
    render_fractal(&frame, 0);
    fractol_commandes();
    mlx_hook(frame.windw, 2, 0, esc_handler, &frame);
    mlx_hook(frame.windw, 17, 0, close_handler, &frame);
    mlx_mouse_hook(frame.windw, mouse_event, &frame);
    mlx_key_hook(frame.windw, keyboard_events, &frame);
    mlx_loop(frame.mlx);
}