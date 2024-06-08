/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ccormon <ccormon@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 10:10:24 by ccormon           #+#    #+#             */
/*   Updated: 2024/06/08 16:03:32 by ccormon          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	display_floor_and_ceiling(t_game *game)
{
	int32_t	x;
	int32_t	y;

	game->param.f.img = mlx_new_image(game->mlx, game->mlx->width / 2,
		game->mlx->height);
	y = 0;
	while (y < game->mlx->height / 2)
	{
		x = 0;
		while (x < game->mlx->width)
			mlx_put_pixel(game->param.f.img, x++, y, game->param.f.rgb);
		y++;
	}
	game->param.c.img = mlx_new_image(game->mlx, game->mlx->width / 2,
		game->mlx->height);
	while (y < game->mlx->height)
	{
		x = 0;
		while (x < game->mlx->width)
			mlx_put_pixel(game->param.c.img, x++, y, game->param.c.rgb);
		y++;
	}
	mlx_image_to_window(game->mlx, game->param.f.img, 0, 0);
	mlx_image_to_window(game->mlx, game->param.c.img, 0, game->mlx->height / 2);
}

bool	display_map(t_game *game)
{
	game->mlx = mlx_init(320, 200, "tetraedre3d", true);
	if (!game->mlx)
		return (false);
	display_floor_and_ceiling(game);
	start_game(game);
	mlx_terminate(game->mlx);
	return (true);
}
